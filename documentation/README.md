CS23710
=======

C and Unix Programming assignment, to build and run the application, cd into the src directory, and run:

    make
    make test

If you just run the binary by itself it will provide you with the command line options and documentation. 

    Usage:
      ./main --observer <observer_locations_file> --sighting <cetacean_file>
      ./main -o <observer_locations_file> -s <cetacean_file>
      ./main --help
      ./main --version

    Options:
       -o FILE, --observer FILE    The file of observers information.
       -s FILE, --sighting FILE    The file of sightings information.
       -h --help             Show this screen.
       -v --version             Show version.
 
    Legend:
       A = Averaged
       D = Dolphin
       P = Porpoise
