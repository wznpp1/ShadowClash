# $1                $2                $3
# Dir            originGateway   Operation(start/stop)

if [ "$3" = "start" ]
then

    # set tun device to be the default gateway
    route delete default
    route add default 240.0.0.1
    route add default "$2" -ifscope en0

    # bypass LAN
    route add 10.0.0.0/8 "$2"
    route add 172.16.0.0/12 "$2"
    route add 192.168.0.0/16 "$2"

    cd "$1";
    for line in `cat ip.txt`
    do
        # add proxy server bypass tun device
        route add $line/32 "$2"
    done

elif [ "$3" = "stop" ]
then

    # set tun device back
    route delete default
    route add default "$2"

    # delete bypass LAN
    route delete 10.0.0.0/8 "$2"
    route delete 172.16.0.0/12 "$2"
    route delete 192.168.0.0/16 "$2"

    cd "$1";
    for line in `cat ip.txt`
    do
        # delete proxy server from route table
        route delete $line/32 "$2"
    done
    killall -9 tun2socks
fi
