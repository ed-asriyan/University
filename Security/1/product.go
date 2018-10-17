package main

import (
	"fmt"
	"io/ioutil"

	"./key_generator"
)

func main() {
	key, err := ioutil.ReadFile(KEY_PATH)

	if err != nil {
		fmt.Println("Key file not found")
		return
	}

	checkResult, err := key_generator.Check(string(key))

	if err != nil {
		fmt.Println(err)
		return
	}

	fmt.Println(checkResult)
}
