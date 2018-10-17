package main

import (
	"fmt"
	"io/ioutil"

	"./license"
)

func main() {
	key, error := license.Generate()

	if error != nil {
		fmt.Println(error)
		return
	}

	ioutil.WriteFile(KEY_PATH, []byte(key), 0644)
}
