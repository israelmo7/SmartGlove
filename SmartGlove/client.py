from socket import *

def main():


	address = ("127.0.0.1", 80)
    
	my_soc = socket()
    
	my_soc.connect(address)
    
	ax = 0
	ay = 0
	az = 0
	f_zero = 0
	f_one = 0
	f_two = 0
      

	while(True):

                
		x = raw_input("Enter Axis: ")
		if x == "e" or x == "E":
			break
		sigh = raw_input("Enter sigh: ")
		
		if x != "d":
			if "f" in x:
				if "1" in x:
					f_zero = f_zero+1 if sigh == "+"else f_zero-1
				if "2" in x:
					f_one = f_one+1 if sigh == "+" else f_one-1
				if "3" in x:
					f_two = f_two+1 if sigh == "+" else f_one-1
			elif "a" in x:
				if "x" in x:
					ax = ax+1 if sigh == "+" else ax-1
				if "y" in x:
					ay = ay+1 if sigh == "+" else ay-1
				if "z" in x:
					az = az+1 if sigh == "+" else az-1
			
			
		
		temp = str(f_zero).zfill(2) + str(f_one).zfill(2) + str(f_two).zfill(2) + "0000" + ("+" if ax >= 0 else "-")+ str(abs(ax)).zfill(2) + ("+" if ay >= 0 else "-")+ str(abs(ay)).zfill(2) + ("+" if az >= 0 else "-")+ str(abs(az)).zfill(2)
		my_soc.send(temp)      

	my_soc.close()

main()
