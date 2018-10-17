package license

import "go/types"

type GeneratorError types.Error
type CheckerError types.Error

func (g GeneratorError) Error() string {
	return "Can not generate a license"
}

func (g CheckerError) Error() string {
	return "Can not check the license"
}
