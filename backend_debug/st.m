clc
close all
clear all

vs = load('vibsig.txt') ; % sound (vibration) signal 

vs = vs(2:end) ; % ignore first index 

fid = fopen('mcode.txt') ; % morse code symbols

line = fgets(fid) ; 

while ischar(line) ; 
    disp (line)  
    line = fgets(fid) ; 
end

fclose(fid) ; 

msound = [] ; 
f = 2*261.626 ; 
T = 1/f ; 

fs = 22050 ; % sampling frequency 

%ddur = 0.06 ; % desired duration
for k = 1:length(vs) 

if mod(k,2) == 0 

ddur = vs(k) / 1000 ; % ms  
adur = floor(ddur/T) * T ; % integer period adjustment
N = fs*adur ; 

t = [0:(N-1)] / fs ;

msound = [ msound (0*t) ] ; % silence 

else
ddur = vs(k) / 1000 ; % ms  
adur = floor(ddur/T) * T ; % integer period adjustment
N = fs*adur ; 

t = [0:(N-1)] / fs ;

msound = [ msound sin(2*pi*f*t) ] ;  

end 

end

wavwrite(msound,fs,'morse_signal') ; 

