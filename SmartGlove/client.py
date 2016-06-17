from socket import *

def main():


	address = ("127.0.0.1", 80)
    
	my_soc = socket()
    
	my_soc.connect(address)
    
	#ax = 0
	#ay = 0
	#az = 0
	#f_zero = 0
	#f_one = 0
	#f_two = 0
      

	#while(True):

                
		#x = raw_input("Enter Axis: ")
		#if x == "e" or x == "E":
		#	break
		#sigh = raw_input("Enter sigh: ")
		#
		#if x != "d":
		#	if "f" in x:
		#		if "1" in x:
		#			f_zero = f_zero+1 if sigh == "+"else f_zero-1
		#		if "2" in x:
		#			f_one = f_one+1 if sigh == "+" else f_one-1
		#		if "3" in x:
		#			f_two = f_two+1 if sigh == "+" else f_one-1
		#	elif "a" in x:
		#		if "x" in x:
		#			ax = ax+1 if sigh == "+" else ax-1
		#		if "y" in x:
		#			ay = ay+1 if sigh == "+" else ay-1
		#		if "z" in x:
		#			az = az+1 if sigh == "+" else az-1
		#	
		#	
		#
		#temp = str(f_zero).zfill(2) + str(f_one).zfill(2) + str(f_two).zfill(2) + "0000" + ("+" if ax >= 0 else "-")+ str(abs(ax)).zfill(2) + ("+" if ay >= 0 else "-")+ str(abs(ay)).zfill(2) + ("+" if az >= 0 else "-")+ str(abs(az)).zfill(2)
	#	my_soc.send(temp)      

	
	values1 = ("00", "25", "05", "25", "05", "+01+05+05")
	values2 = ("00", "25", "05", "25", "05", "+11+05+05")
	values3 = ("00", "25", "05", "25", "05", "+21+05+05")
	values4 = ("00", "25", "05", "25", "05", "+31+05+05")
	values5 = ("00", "25", "05", "25", "05", "+41+05+05")
	values6 = ("00", "25", "05", "25", "05", "+51+05+05")
	values7 = ("00", "25", "05", "25", "05", "+61+05+05")
	values8 = ("00", "25", "05", "25", "05", "+51+05+05")
	values9 = ("00", "25", "05", "25", "05", "+41+15+05")
	values10 = ("00", "25", "05", "25", "05", "+31+25+05")
	values11 = ("00", "25", "05", "25", "05", "+21+35+05")
	values12 = ("00", "25", "05", "25", "05", "+11+45+05")
	values13 = ("00", "25", "05", "25", "05", "+01+55+05")
	values14 = ("00", "25", "05", "25", "05", "-11+55+05")
	values15 = ("11", "25", "05", "25", "05", "-11+55+05")
	values0 = ("11", "25", "05", "25", "05", "-11+55+05")
	values00 = ("11", "25", "05", "25", "05", "-11+55+05")
	values000 = ("11", "25", "05", "25", "05", "+51+55+05")
	arr = ["".join(values1), "".join(values2), "".join(values3), "".join(values4), "".join(values5), "".join(values6), "".join(values7), "".join(values8), "".join(values9), "".join(values10), "".join(values11), "".join(values12), "".join(values13), "".join(values14), "".join(values15), "".join(values0), "".join(values00), "".join(values000)]
	
	for i in arr:
		my_soc.send(i)
	
	my_soc.close()

main()
