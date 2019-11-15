package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"os"

	"github.com/bmstu-rsoi/lab1-ci-cd-ed-asriyan/store"
)

func HelloName(w http.ResponseWriter, r *http.Request) {
	key := r.URL.Path
	switch r.Method {
	case "GET":
		value, err := store.Get(key)
		if err == nil {
			fmt.Fprintln(w, value)
		} else {
			if err.Error() == "redis: nil" {
				w.WriteHeader(http.StatusNotFound)
			} else {
				w.WriteHeader(http.StatusInternalServerError)
				fmt.Fprintln(w, err)
			}
		}
	case "POST":
		value, err := ioutil.ReadAll(r.Body)
		if err == nil {
			err = store.Set(key, string(value))
		}
		if err == nil {
			w.WriteHeader(http.StatusCreated)
		} else {
			w.WriteHeader(http.StatusInternalServerError)
			fmt.Fprintln(w, err)
		}
	}
}

func main() {
	portStr := os.Getenv("PORT")
	if portStr == "" {
		portStr = "8080"
	}

	http.HandleFunc("/", HelloName)
	err := http.ListenAndServe(":"+portStr, nil)
	if err != nil {
		log.Fatal("ListenAndServe: ", err)
	}
}
