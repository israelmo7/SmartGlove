from socket import *

def main():


	address = ("127.0.0.1", 80)
    
	my_soc = socket()
    
	my_soc.connect(address)
    
	values1 = ("-100", "+020", "+080", "+070", "+080", "-123+456-789")
	values2 = ("-050", "+020", "+070", "+080", "+070", "-123+456-789")

	values3 = ("-060", "+020", "+050", "+080", "+060", "-123+456-789")

	values4 = ("-030", "+020", "+040", "+080", "-060", "-123+456-789")

	values5 = ("-040", "+020", "+030", "+080", "-070", "-123+456-789")

	values6 = ("-100", "+020", "+010", "+090", "-080", "-123+456-789")
	

	arr = ["".join(values1), "".join(values2), "".join(values3)\
	, "".join(values4), "".join(values5), "".join(values6),"".join(values6),"".join(values6),"".join(values6)]



	for i in arr:
		my_soc.send(i)
		
	values1 = ("-100", "+020", "+080", "+070", "+070", "-123+456-789")
	values2 = ("-050", "+020", "+080", "+080", "+070", "-123+456-789")

	values3 = ("-040", "+020", "+080", "+080", "+070", "-123+456-789")

	values4 = ("-040", "+020", "+080", "+080", "+070", "-123+456-789")

	values5 = ("-040", "+020", "+080", "+080", "+070", "-123+456-789")

	values6 = ("+100", "+020", "+080", "+090", "+070", "-123+456-789")
	

	arr = ["".join(values1),"".join(values1),"".join(values1),"".join(values1),"".join(values1),"".join(values1),"".join(values1),"".join(values1),"".join(values1),"".join(values1),"".join(values1),"".join(values1),"".join(values1),"".join(values1), "".join(values2), "".join(values3)\
	, "".join(values4), "".join(values5), "".join(values6),"".join(values6),"".join(values6),"".join(values6)]
	
	for i in arr:
		my_soc.send(i)

	my_soc.close()

main()
