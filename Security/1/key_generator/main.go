package key_generator

import (
	"github.com/shirou/gopsutil/disk"
)

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

	result, err := encrypt(secret, AES_KEY)
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

	result, err := decrypt(key, AES_KEY)
	if err != nil {
		return false, err
	}

	return secret == string(result), nil
}
