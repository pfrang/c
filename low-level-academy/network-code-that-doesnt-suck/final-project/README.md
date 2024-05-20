In this project we are generaitng a listening server and a client code in the folders /srv and /cli respectively


On running make you will initialize the server and client can connect on running the binary ./bin/dbcli 127.0.0.1

First when client is connecting we are checking if the protocol matches, if it we are upgrading the client state to some other state that allows them to pass data to our server


run the final program with ./bin/dbcli -p 8080 -h 127.0.0.1 -a "Name, Addres, Hours" -l
