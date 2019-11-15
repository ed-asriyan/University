package store

import (
	"github.com/go-redis/redis/v7"
	"os"
)

var options, _ = redis.ParseURL(os.Getenv("REDIS_URL"))
var client = redis.NewClient(options)

func Get(key string) (string, error) {
	return client.Get(key).Result()
}

func Set(key, value string) error {
	return client.Set(key, value, 0).Err()
}
