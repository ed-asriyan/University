package main

import (
	"log"
	"net/http"
	"os"

	"github.com/bmstu-rsoi/lab1-ci-cd-ed-asriyan/store"
)

func main() {
	redisStore := store.CreateStore(os.Getenv("REDIS_URL"))

	server := KeyValueStoreServer{&redisStore}

	portStr := os.Getenv("PORT")
	if portStr == "" {
		portStr = "8080"
	}

	http.Handle("/", &server)
	err := http.ListenAndServe(":"+portStr, nil)
	if err != nil {
		log.Fatal("ListenAndServe: ", err)
	}
}
