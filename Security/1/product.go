package main

import (
	"fmt"
	"io/ioutil"

	"./license"
)

func main() {
	key, err := ioutil.ReadFile(KEY_PATH)

	if err != nil {
		fmt.Println("Key file not found")
		return
	}

	checkResult, err := license.Check(string(key))

	if err != nil {
		fmt.Println(err)
		return
	}

	fmt.Println(checkResult)
}
