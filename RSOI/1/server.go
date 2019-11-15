package main

import (
	"fmt"
	"github.com/bmstu-rsoi/lab1-ci-cd-ed-asriyan/store"
	"io/ioutil"
	"net/http"
)

type KeyValueStoreServer struct {
	store store.Store
}

func (server *KeyValueStoreServer) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	key := r.URL.Path
	switch r.Method {
	case "DELETE":
		err := server.store.DeleteValue(key)
		if err == nil {
			w.WriteHeader(http.StatusOK)
		} else {
			if err.Error() == "key does not exists" {
				w.WriteHeader(http.StatusNotFound)
			} else {
				w.WriteHeader(http.StatusInternalServerError)
				fmt.Fprintln(w, err)
			}
		}
	case "GET":
		value, err := server.store.GetValue(key)
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
			err = server.store.SetValue(key, string(value))
		}
		if err == nil {
			w.WriteHeader(http.StatusCreated)
		} else {
			w.WriteHeader(http.StatusInternalServerError)
			fmt.Fprintln(w, err)
		}
	}
}
