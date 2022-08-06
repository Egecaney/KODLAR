% ELE407 - Preliminary Work 5
% Egemen Can Ayduðan - 21728036

%% Question 1 (Check Functions)

% Checking rec(M)
CheckRec1 = rec(5);
CheckRec2 = boxcar(5);
figure(1);
subplot(1,2,1);
stem(CheckRec1); 
title('Rectangular Window (My Function)');
subplot(1,2,2);
stem(CheckRec2); 
title('Rectangular Window (Matlab Built-In Function)');

% Checking bart(M)
CheckBart1 = bart(15);
CheckBart2 = bartlett(15);
figure(2);
subplot(1,2,1);
stem(CheckBart1); 
title('Bartlett Window (My Function)');
subplot(1,2,2);
stem(CheckBart2); 
title('Bartlett Window (Matlab Built-In Function)');

% Checking bla(M)
CheckBla1 = bla(20);
CheckBla2 = blackman(20);
figure(3);
subplot(1,2,1);
stem(CheckBla1); 
title('Blackman Window (My Function)');
subplot(1,2,2);
stem(CheckBla2); 
title('Blackman Window (Matlab Built-In Function)');

%% Question 2
% M=40 Rectangular
Rec40 = rec(40);
figure(4);
freqz(Rec40,100); title('Magnitude Spectra for Rectangular Window for M=40');
% M=40 Bartlett
Bart40=bart(40);
figure(5);
freqz(Bart40,100); title('Magnitude Spectra for Bartlett Window for M=40')
% M=40 Blackman
Bla40 = bla(40);
figure(6);
freqz(Bla40,100); title('Magnitude Spectra for Blackman Window for M=40')

% M=80 Rectangular
Rec80 = rec(80);
figure(7);
freqz(Rec80,100); title('Magnitude Spectra for Rectangular Window for M=80')
% M=80 Bartlett
Bart80=bart(80);
figure(8);
freqz(Bart80,100); title('Magnitude Spectra for Bartlett Window for M=80')
% M=80 Blackman
Bla80=bla(80);
figure(9);
freqz(Bla80,100); title('Magnitude Spectra for Blackman Window for M=80')

%% Question 3
n = 0:1:255;

x1 = cos(2*pi*0.242*n)+cos(2*pi*0.258*n);
X1 = fftshift(abs(fft(x1)));
FreqAxisX1 = linspace(-1,1,length(X1));

x2 = 2*cos(2*pi*0.25*n)+cos(2*pi*0.008*n);
X2 = fftshift(abs(fft(x2)));
FreqAxisX2 = linspace(-1,1,length(X2));

x3 = cos(2*pi*0.29*n);
X3 = fftshift(abs(fft(x3)));
FreqAxisX3 = linspace(-1,1,length(X3));

figure(10);
subplot(2,2,1);
plot(x1); title('Signal x1 Time Waveform'); ylabel('Magnitude'); xlabel('Sample Number');
subplot(2,2,2);
plot(x2); title('Signal x2 Time Waveform'); ylabel('Magnitude'); xlabel('Sample Number');
subplot(2,2,3);
plot(FreqAxisX1,X1); title('Magnitude Spectrum of x1'); ylabel('Magnitude'); xlabel('Normalized Frequency');
subplot(2,2,4);
plot(FreqAxisX2,X2); title('Magnitude Spectrum of x2'); ylabel('Magnitude'); xlabel('Normalized Frequency');

%% Question 4
% Signal x1 [n] Using Rectangular Windows of Length M=40
x1Rec40 = [rec(40).' zeros(1,215)];
x1Rec40 = x1Rec40.*x1;
X1Rec40 = fftshift(abs(fft(x1Rec40)));
FreqAxisX1Rec40 = linspace(-1,1,length(X1Rec40));

% Signal x1 [n] Using Rectangular Windows of Length M=80
x1Rec80 = [rec(80).' zeros(1,175)];
x1Rec80 = x1Rec80.*x1;
X1Rec80 = fftshift(abs(fft(x1Rec80)));
FreqAxisX1Rec80 = linspace(-1,1,length(X1Rec80));

figure(11);
subplot(3,1,1);
plot(FreqAxisX1,X1);
title('Magnitude Spectrum of x1[n]'); ylabel('Magnitude'); xlabel('Normalized Frequency');
subplot(3,1,2);
plot(FreqAxisX1Rec40,X1Rec40);
title('Magnitude Spectrum of Rectangular Windowed x1[n] M=40'); ylabel('Magnitude'); xlabel('Normalized Frequency');
subplot(3,1,3);
plot(FreqAxisX1Rec80,X1Rec80);
title('Magnitude Spectrum of Rectangular Windowed x1[n] M=80'); ylabel('Magnitude'); xlabel('Normalized Frequency');

%% Question 5
% Rectangular Window
Recx3 = [rec(57).' zeros(1,198)];
Recx3 = x3.*Recx3;
RecX3=fftshift(abs(fft(Recx3,256)));
FreqAxisRecX3=linspace(-1,1,length(RecX3));

% Bartlett Window
Bartx3 = [bart(57).' zeros(1,198)];
Bartx3 = x3.*Bartx3;
BartX3 = fftshift(abs(fft(Bartx3,256)));
FreqAxisBartX3 = linspace(-1,1,length(BartX3));

figure(12);
subplot(3,1,1);
plot(FreqAxisX3,X3);
title('Magnitude Spectrum of x3[n]'); ylabel('Magnitude'); xlabel('Normalized Frequency');
subplot(3,1,2);
plot(FreqAxisRecX3,RecX3);
title('Rectangular Window of x3[n]'); ylabel('Magnitude'); xlabel('Normalized Frequency');
subplot(3,1,3)
plot(FreqAxisBartX3,BartX3); 
title('Bartlett Window x3[n]'); ylabel('Magnitude'); xlabel('Normalized Frequency');

%% Question 7
load('lowpass.mat')
figure(13);
impz(Num); title('Impulse Response of LPF');
figure(14);
freqz(Num,1,512); title('Magnitude and Phase Response of LPF');

%% Question 8
load('bandpass.mat')
figure(15);
impz(Numband); title('Impulse Response of BPF');
figure(16);
freqz(Numband,1,512); title('Magnitude and Phase Response of BPF');