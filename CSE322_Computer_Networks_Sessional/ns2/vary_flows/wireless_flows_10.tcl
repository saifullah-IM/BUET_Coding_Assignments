# simulator
set ns [new Simulator]


# ======================================================================
# Define options

set val(chan)         Channel/WirelessChannel  ;# channel type
set val(prop)         Propagation/TwoRayGround ;# radio-propagation model
set val(ant)          Antenna/OmniAntenna      ;# Antenna type
set val(ll)           LL                       ;# Link layer type
set val(ifq)          Queue/DropTail/PriQueue  ;# Interface queue type
set val(ifqlen)       50                       ;# max packet in ifq
set val(netif)        Phy/WirelessPhy          ;# network interface type
set val(mac)          Mac/802_11               ;# MAC type
set val(rp)           DSDV                     ;# ad-hoc routing protocol 
set val(nn)           40                       ;# number of mobilenodes
set val(xlen)         500                      ;# length of one side of area
# =======================================================================

# trace file
set trace_file [open trace_flows_10.tr w]
$ns trace-all $trace_file

# nam file
set nam_file [open animation_flows_10.nam w]
$ns namtrace-all-wireless $nam_file $val(xlen) $val(xlen)

# topology: to keep track of node movements
set topo [new Topography]
$topo load_flatgrid $val(xlen) $val(xlen);# area


# general operation director for mobilenodes
create-god $val(nn)


# node configs
# ======================================================================

# $ns node-config -addressingType flat or hierarchical or expanded
#                  -adhocRouting   DSDV or DSR or TORA
#                  -llType	   LL
#                  -macType	   Mac/802_11
#                  -propType	   "Propagation/TwoRayGround"
#                  -ifqType	   "Queue/DropTail/PriQueue"
#                  -ifqLen	   50
#                  -phyType	   "Phy/WirelessPhy"
#                  -antType	   "Antenna/OmniAntenna"
#                  -channelType    "Channel/WirelessChannel"
#                  -topoInstance   $topo
#                  -energyModel    "EnergyModel"
#                  -initialEnergy  (in Joules)
#                  -rxPower        (in W)
#                  -txPower        (in W)
#                  -agentTrace     ON or OFF
#                  -routerTrace    ON or OFF
#                  -macTrace       ON or OFF
#                  -movementTrace  ON or OFF

# ======================================================================

$ns node-config -adhocRouting $val(rp) \
                -llType $val(ll) \
                -macType $val(mac) \
                -ifqType $val(ifq) \
                -ifqLen $val(ifqlen) \
                -antType $val(ant) \
                -propType $val(prop) \
                -phyType $val(netif) \
                -topoInstance $topo \
                -channelType $val(chan) \
                -agentTrace ON \
                -routerTrace ON \
                -macTrace OFF \
                -movementTrace OFF


#function to get grid size
proc getheight {nn} {
    set ans 1
    for {set i 2} {$i <= $nn } {incr i} {
        if {[expr $nn % $i] == 0} {
            if {$ans < [expr $nn / $i]} {
                set ans $i
            } else {
                break
            }

        }
    } 
    return $ans
}

# create nodes
set col [getheight $val(nn)]
set yone [expr $val(xlen) / ($col-1)]
set col [expr $val(nn) / $col]
set xone [expr $val(xlen) / ($col-1)]
for {set i 0} {$i < $val(nn) } {incr i} {
    set node($i) [$ns node]
    $node($i) random-motion 0       ;# disable random motion

    set xx [expr $i % $col]
    set xx [expr $xx * $xone]
    set yy [expr $i / $col]
    set yy [expr $yy * $yone]

    $node($i) set X_ $xx
    $node($i) set Y_ $yy
    $node($i) set Z_ 0

    $ns initial_node_pos $node($i) 20

    set speed [expr {ceil(rand() * 5)}]

    set des(x) [expr {ceil(rand() * ($val(xlen)-1))}]
    set des(y) [expr {ceil(rand() * ($val(xlen)-1))}]
    
    set time [expr {ceil(rand() * 10)}]
    set time [expr $time+2]
    
    $ns at $time "$node($i) setdest $des(x) $des(y) $speed"
} 



# Traffic
set val(nf)         10                ;# number of flows

set mysrc [expr {int(floor(rand() * $val(nn)))}]  ;# constant source

for {set i 0} {$i < $val(nf)} {incr i} {
    set src $mysrc
    set dest [expr {int(floor(rand() * $val(nn)))}]
    while {$dest == $mysrc} {
        set dest [expr {int(floor(rand() * $val(nn)))}]   ;# get a destination unequal to source
    }

    # Traffic config
    # create agent
    set udp [new Agent/UDP]
    set udp_sink [new Agent/Null]
    # attach to nodes
    $ns attach-agent $node($src) $udp
    $ns attach-agent $node($dest) $udp_sink
    # connect agents
    $ns connect $udp $udp_sink
    $udp set fid_ $i

    # Traffic generator
    set etp [new Application/Traffic/Exponential]
    # attach to agent
    $etp attach-agent $udp
    
    # start traffic generation
    $ns at 1.0 "$etp start"
}



# End Simulation

# Stop nodes
for {set i 0} {$i < $val(nn)} {incr i} {
    $ns at 50.0 "$node($i) reset"
}

# call final function
proc finish {} {
    global ns trace_file nam_file
    $ns flush-trace
    close $trace_file
    close $nam_file
}

proc halt_simulation {} {
    global ns
    puts "Simulation ending"
    $ns halt
}

$ns at 50.0001 "finish"
$ns at 50.0002 "halt_simulation"




# Run simulation
puts "Simulation starting"
$ns run

