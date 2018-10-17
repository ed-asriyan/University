package key_generator

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

const AES_KEY = "the-key-has-to-be-32-bytes-long!"

func encrypt(plainTextString string, keyString string) ([]byte, error) {
	c, err := aes.NewCipher([]byte(keyString))
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

	return gcm.Seal(nonce, nonce, []byte(plainTextString), nil), nil
}

func decrypt(ciphertextString string, keyString string) ([]byte, error) {
	cipherText := []byte(ciphertextString)

	c, err := aes.NewCipher([]byte(keyString))
	if err != nil {
		return nil, err
	}

	gcm, err := cipher.NewGCM(c)
	if err != nil {
		return nil, err
	}

	nonceSize := gcm.NonceSize()
	if len(cipherText) < nonceSize {
		return nil, errors.New("cipherText too short")
	}

	nonce, cipherText := cipherText[:nonceSize], cipherText[nonceSize:]
	return gcm.Open(nil, nonce, []byte(cipherText), nil)
}
