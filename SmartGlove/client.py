from socket import *

def main():


	address = ("127.0.0.1", 80)
    
	my_soc = socket()
    
	my_soc.connect(address)
    
	values1 = ("10", "20", "80", "70", "80", "-15+45-78")
	
	values2 = ("50", "20", "70", "80", "70", "-12+45-78")

	values3 = ("60", "20", "50", "80", "60", "-10+45-78")

	#values4 = ("30", "20", "40", "80", "60", "-50+45-78")

	#values5 = ("40", "20", "30", "80", "70", "+50+45-78")

	#values6 = ("10", "20", "10", "90", "80", "+90+45-78")
	

	arr = ["".join(values1), "".join(values2), "".join(values3)]#\
	#, "".join(values4), "".join(values5), "".join(values6),"".join(values6),"".join(values6),"".join(values6)]



	for i in arr:
		my_soc.send(i)
		
	#values1 = ("-100", "+020", "+080", "+070", "+070", "-123+456-789")
	#values2 = ("-050", "+020", "+080", "+080", "+070", "-123+456-789")

	#values3 = ("-040", "+020", "+080", "+080", "+070", "-123+456-789")

	#values4 = ("-040", "+020", "+080", "+080", "+070", "-123+456-789")

	#values5 = ("-040", "+020", "+080", "+080", "+070", "-123+456-789")

	#values6 = ("+100", "+020", "+080", "+090", "+070", "-123+456-789")
	

	#arr = ["".join(values1),"".join(values1),"".join(values1),"".join(values1),"".join(values1),"".join(values1),"".join(values1),"".join(values1),"".join(values1),"".join(values1),"".join(values1),"".join(values1),"".join(values1),"".join(values1), "".join(values2), "".join(values3)\
	#, "".join(values4), "".join(values5), "".join(values6),"".join(values6),"".join(values6),"".join(values6)]
	
	#for i in arr:
	#	my_soc.send(i)

	my_soc.close()

main()
