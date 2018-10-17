package key_generator

import (
	"github.com/shirou/gopsutil/disk"
	"go/types"
)

type GeneratorError types.Error
type CheckerError types.Error

func (g GeneratorError) Error() string {
	return "Can not generate a key"
}

func (g CheckerError) Error() string {
	return "Can not check a key"
}

func getSecret() (string, error) {
	serial := disk.GetDiskSerialNumber("/dev/sda")

	if serial == "" {
		return "", GeneratorError{}
	}

	return serial, nil
}

func Generate() (string, error) {
	return getSecret()
}

func Check(key string) (bool, error) {
	secret, error := getSecret()

	if error != nil {
		return false, CheckerError{}
	}

	return key == secret, nil
}