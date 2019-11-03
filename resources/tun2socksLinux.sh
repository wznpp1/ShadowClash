# $1                $2                $3
# Dir            originGateway   Operation(start/stop)

if [ "$3" = "start" ]
then

    # Active tun device
    ip addr add 240.0.0.1/24 dev tun1
    ip link set dev tun1 up
    # set tun device to be the default gateway
    ip route del default
    ip route add default via 240.0.0.1

    # bypass LAN
    ip route add 10.0.0.0/8 via "$2"
    ip route add 172.16.0.0/12 via "$2"
    ip route add 192.168.0.0/16 via "$2"

    cd "$1";
    for line in `cat ip.txt`
    do
        # add proxy server bypass tun device
        ip route add $line/32 via "$2"
    done

elif [ "$3" = "stop" ]
then

    # set tun device back
    ip route del default
    ip route add default via "$2"

    # delete bypass LAN
    ip route del 10.0.0.0/8 via "$2"
    ip route del 172.16.0.0/12 via "$2"
    ip route del 192.168.0.0/16 via "$2"

    cd "$1";
    for line in `cat ip.txt`
    do
        # delete proxy server from route table
        ip route del $line/32 via "$2"
    done
    killall -9 tun2socks
fi
