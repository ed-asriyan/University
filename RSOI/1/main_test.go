package main

import (
	"errors"
	"io"
	"net/http"
	"net/http/httptest"
	"strings"
	"testing"
)

type MockedStore map[string]string

func (m *MockedStore) GetValue(key string) (string, error) {
	a, ok := (*m)[key]
	if !ok {
		return "", errors.New("redis: nil")
	}
	return a, nil
}

func (m *MockedStore) SetValue(key, value string) error {
	(*m)[key] = value
	return nil
}

func getResponse(method, path string, body io.Reader, initialStore *MockedStore) (*httptest.ResponseRecorder, error) {
	req, err := http.NewRequest(method, path, body)
	if err != nil {
		return nil, err
	}

	rr := httptest.NewRecorder()
	Handler := http.Handler(&KeyValueStoreServer{initialStore})

	Handler.ServeHTTP(rr, req)

	return rr, nil
}

func TestGetExistingKey(t *testing.T) {
	const expectedValue = "value"
	rr, err := getResponse("GET", "/value", nil, &MockedStore{"/value": expectedValue})
	if err != nil {
		t.Fatal(err)
	}

	if status := rr.Code; status != http.StatusOK {
		t.Errorf("Handler returned wrong status code: got %v want %v", status, http.StatusOK)
	}

	if rr.Body.String() != expectedValue+"\n" {
		t.Errorf("Handler returned unexpected body: %v", rr.Body.String())
	}
}

func TestGetNonExistingKey(t *testing.T) {
	const key = "/some-value"
	rr, err := getResponse("GET", key, nil, &MockedStore{})
	if err != nil {
		t.Fatal(err)
	}

	if status := rr.Code; status != http.StatusNotFound {
		t.Errorf("Handler returned wrong status code: got %v want %v", status, http.StatusNotFound)
	}

	if rr.Body.String() != "" {
		t.Errorf("Handler returned unexpected body:  %v", rr.Body.String())
	}
}

func TestSetNonExistingKey(t *testing.T) {
	const key = "/vv"
	const expectedValue = "value"
	store := MockedStore{}
	rr, err := getResponse("POST", key, strings.NewReader(expectedValue), &store)
	if err != nil {
		t.Fatal(err)
	}

	if status := rr.Code; status != http.StatusCreated {
		t.Errorf("Handler returned wrong status code: got %v want %v", status, http.StatusOK)
	}

	if rr.Body.String() != "" {
		t.Errorf("Handler returned unexpected body: %v", rr.Body.String())
	}

	if store[key] != expectedValue {
		t.Errorf("wrong value in store: %v", store[key])
	}
}

func TestSetExistingKey(t *testing.T) {
	const key = "/vv"
	const expectedValue = "value"
	store := MockedStore{key: "anotherValue"}
	rr, err := getResponse("POST", key, strings.NewReader(expectedValue), &store)
	if err != nil {
		t.Fatal(err)
	}

	if status := rr.Code; status != http.StatusCreated {
		t.Errorf("Handler returned wrong status code: got %v want %v", status, http.StatusOK)
	}

	if rr.Body.String() != "" {
		t.Errorf("Handler returned unexpected body: %v", rr.Body.String())
	}

	if store[key] != expectedValue {
		t.Errorf("wrong value in store: %v", store[key])
	}
}
