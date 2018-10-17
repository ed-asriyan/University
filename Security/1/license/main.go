package license

import (
	"github.com/shirou/gopsutil/disk"
)

const aesKey = "the-key-has-to-be-32-bytes-long!"

func getSecret() string {
	return disk.GetDiskSerialNumber("/dev/sda")
}

func Generate() (string, error) {
	secret := getSecret()
	if secret == "" {
		return "", GeneratorError{}
	}

	result, err := encrypt(secret, aesKey)
	if err != nil {
		return "", GeneratorError{}
	}

	return result, nil
}

func Check(key string) (bool, error) {
	secret := getSecret()

	result, err := decrypt(key, aesKey)
	if err != nil {
		return false, CheckerError{}
	}

	return secret == result, nil
}
