package event

type Reader interface {
	Run(event chan<- string)
}
