package key_generator

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"github.com/shirou/gopsutil/disk"
	"go/types"
	"io"
)

type GeneratorError types.Error
type CheckerError types.Error

func (g GeneratorError) Error() string {
	return "Can not generate a key"
}

func (g CheckerError) Error() string {
	return "Can not check a key"
}

const AES_KEY = "the-key-has-to-be-32-bytes-long!"

func encrypt(plaintext []byte, key []byte) ([]byte, error) {
	c, err := aes.NewCipher(key)
	if err != nil {
		return nil, err
	}

	gcm, err := cipher.NewGCM(c)
	if err != nil {
		return nil, err
	}

	nonce := make([]byte, gcm.NonceSize())
	if _, err = io.ReadFull(rand.Reader, nonce); err != nil {
		return nil, err
	}

	return gcm.Seal(nonce, nonce, plaintext, nil), nil
}

func decrypt(ciphertext []byte, key []byte) ([]byte, error) {
	c, err := aes.NewCipher(key)
	if err != nil {
		return nil, err
	}

	gcm, err := cipher.NewGCM(c)
	if err != nil {
		return nil, err
	}

	nonceSize := gcm.NonceSize()
	if len(ciphertext) < nonceSize {
		return nil, errors.New("ciphertext too short")
	}

	nonce, ciphertext := ciphertext[:nonceSize], ciphertext[nonceSize:]
	return gcm.Open(nil, nonce, ciphertext, nil)
}

func getSecret() (string, error) {
	serial := disk.GetDiskSerialNumber("/dev/sda")

	if serial == "" {
		return "", GeneratorError{}
	}

	return serial, nil
}

func Generate() (string, error) {
	secret, err := getSecret()
	if err != nil {
		return "", err
	}
	result, err := encrypt([]byte(secret), []byte(AES_KEY))
	if err != nil {
		return "", err
	}
	return string(result), nil
}

func Check(key string) (bool, error) {
	secret, err := getSecret()
	if err != nil {
		return false, err
	}

	result, err := decrypt([]byte(key), []byte(AES_KEY))
	if err != nil {
		return false, err
	}

	return secret == string(result), nil
}
