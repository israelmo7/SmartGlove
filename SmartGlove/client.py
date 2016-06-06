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

	
	values1 = ("05", "25", "05", "25", "05", "+05+05+05")
	values2 = ("15", "15", "15", "15", "15", "+05+05+05")
	values3 = ("15", "15", "15", "15", "15", "+05+05+05")
	values4 = ("15", "15", "15", "15", "15", "+05+05+05")
	values5 = ("15", "15", "15", "15", "15", "+05+05+05")
	values6 = ("05", "05", "15", "15", "15", "+05+05+05")
	values7 = ("05", "15", "15", "15", "15", "+05+05+05")
	values8 = ("15", "15", "15", "15", "15", "+05+05+05")
	arr = ["".join(values1), "".join(values2), "".join(values3), "".join(values4), "".join(values5), "".join(values6), "".join(values7), "".join(values8)]
	
	for i in arr:
		my_soc.send(i)
	
	my_soc.close()

main()
