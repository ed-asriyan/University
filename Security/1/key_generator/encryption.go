package key_generator

import (
	"crypto/aes"
	"crypto/cipher"
	"crypto/rand"
	"errors"
	"io"
)

func encrypt(plainTextString string, keyString string) (string, error) {
	c, err := aes.NewCipher([]byte(keyString))
	if err != nil {
		return "", err
	}

	gcm, err := cipher.NewGCM(c)
	if err != nil {
		return "", err
	}

	nonce := make([]byte, gcm.NonceSize())
	if _, err = io.ReadFull(rand.Reader, nonce); err != nil {
		return "", err
	}

	return string(gcm.Seal(nonce, nonce, []byte(plainTextString), nil)), nil
}

func decrypt(cipherTextString string, keyString string) (string, error) {
	cipherText := []byte(cipherTextString)

	c, err := aes.NewCipher([]byte(keyString))
	if err != nil {
		return "", err
	}

	gcm, err := cipher.NewGCM(c)
	if err != nil {
		return "", err
	}

	nonceSize := gcm.NonceSize()
	if len(cipherText) < nonceSize {
		return "", errors.New("cipherText too short")
	}

	nonce, cipherText := cipherText[:nonceSize], cipherText[nonceSize:]
	result, err := gcm.Open(nil, nonce, []byte(cipherText), nil)
	if err != nil {
		return "", err
	}
	return string(result), nil
}
