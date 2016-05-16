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
	

	arr = ["".join(values1), "".join(values2), "".join(values3), "".join(values3), "".join(values3), "".join(values3)]
	#, "".join(values4), "".join(values5), "".join(values6),"".join(values6),"".join(values6),"".join(values6)]

	ax = 0
	ay = 0
	my_soc.send("0000000000+00+00+00")
	my_soc.send("0000000000+00+00+00")
      

	while(True):

                
		x = raw_input("Enter Axis: ")
		if x == "e" or x == "E":
			break
		sigh = raw_input("Enter sigh: ")

		if 'x' in x or 'X' in x: # == "X" or x == "x":
			if sigh == "+":
				ax += 1
			elif sigh == "-":
				ax -= 1
				
		if  'y' in x or 'Y' in x: #x == "Y" or x == "y":
			if sigh == "+":
				ay += 1
			elif sigh == "-":
				ay -= 1
			
		
		temp = "0000000000" + ("+" if ax >= 0 else "-")+ str(abs(ax)).zfill(2) + ("+" if ay >= 0 else "-")+ str(abs(ay)).zfill(2) + "+00"
		my_soc.send(temp)      

	my_soc.close()

main()
