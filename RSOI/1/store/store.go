package store

type Store interface {
	GetValue(string) (string, error)
	SetValue(string, string) error
	DeleteValue(string) error
}
