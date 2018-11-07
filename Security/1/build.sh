GOPATH=/tmp

go get -t github.com/shirou/gopsutil/disk
go build -i installer.go config.go
go build -i product.go config.go

