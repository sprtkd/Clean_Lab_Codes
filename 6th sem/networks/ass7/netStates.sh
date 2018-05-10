read -p "Enter Port: "  port_no

echo "************************************************"
echo " "
echo " "
echo "==IF TCP SERVER started, listen=="
echo "==IF TCP CLIENT Connected, Established=="
echo "==IF TCP CLIENT Disconnected, within 120s, Time Wait=="
echo "==IF No TCP SERVER running, blank=="
echo " "
echo " "

echo "************************************************"
echo " "
echo " "
echo "List:"
netstat -an | grep $port_no
echo " "
echo " "
echo "************************************************"
echo " "
