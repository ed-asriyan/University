package main

import (
	"fmt"
	"io/ioutil"

	"./key_generator"
)

func main() {
	key, error := key_generator.Generate()

	if error != nil {
		fmt.Println(error)
		return
	}

	ioutil.WriteFile(KEY_PATH, []byte(key), 0644)
}
