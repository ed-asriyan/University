package store

import (
	"errors"
	"github.com/go-redis/redis/v7"
)

type RedisStore redis.Client

func CreateStore(redisUrl string) RedisStore {
	var options, _ = redis.ParseURL(redisUrl)
	return RedisStore(*redis.NewClient(options))
}

func (s *RedisStore) GetValue(key string) (string, error) {
	return s.Get(key).Result()
}

func (s *RedisStore) SetValue(key, value string) error {
	return s.Set(key, value, 0).Err()
}

func (s *RedisStore) DeleteValue(key string) error {
	if _, err := s.Get(key).Result(); err != nil {
		return errors.New("key does not exists")
	}
	return s.Del(key).Err()
}
