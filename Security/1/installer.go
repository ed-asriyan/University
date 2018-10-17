package main

import (
	"fmt"
	"io/ioutil"

	"./license"
)

func main() {
	key, err := license.Generate()

	if err != nil {
		fmt.Println(err)
		return
	}

	if ioutil.WriteFile(LICENSE_PATH, []byte(key), 0644) != nil {
		fmt.Println("Can not save the license file")
		return
	}
}
