package crm

import (
	"fmt"
	"log"
	"net/http"
)

type AdminPanel struct {
	contentFolder string
	port          int
}

func NewAdminPanel(contentFolder string, port int) *AdminPanel {
	return &AdminPanel{
		contentFolder: contentFolder,
		port:          port,
	}
}

func (p *AdminPanel) Serve() {
	fs := http.FileServer(http.Dir(p.contentFolder))
	http.Handle("/", fs)

	err := http.ListenAndServe(fmt.Sprintf(":%v", p.port), nil)
	if err != nil {
		log.Fatal(err)
	}
}
