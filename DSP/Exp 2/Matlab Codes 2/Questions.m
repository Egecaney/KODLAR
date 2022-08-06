% Egemen Can AYDUÐAN 21728036
% Preliminary Work 2

%% Question 2
b = [0 -0.4944 0.64];
a = [1 -1.3335 0.49];
L = 512;
x = randn(1,L);


y = inout(b,a,x,L);
Y = fftshift(abs(fft(y)));
FrequencyAxisY = -(L/2):(L/length(Y)):((L/2)-(L/length(Y)));

figure (1);
subplot(2,1,1);
plot(y); title('Output'); xlabel('N'); ylabel('Amplitude');
subplot(2,1,2);
plot(FrequencyAxisY,Y); title('Magnitude Spectra'); xlabel('Frequency'); ylabel('Amplitude');

%% Question 3
A = zeros (1,9);
A(1) = 1;
B = [-1,-1];
y3 = myAR(A,B);

%% Question 4
y4 = myMA([1 2],[1 -1]);
z4 = myMA([1 2 3],[1 -2 1]);

%% Question 5
x5 = randn(1,1024);
X5 = fftshift(abs(fft(x5)));
FrequencyAxisX5 = -(1024/2):(1024/length(X5)):((1024/2)-(1024/length(X5)));

figure(2);
subplot(2,1,1);
plot(x5); 
title('Gaussian Distributed Signal'); ylabel('Amplitude');
subplot(2,1,2);
plot(FrequencyAxisX5,X5); 
title('Magnitude Spectra'); xlabel('Frequency'); ylabel('Amplitude');

%% Question 6
%6.A
Length6 = 1024;
x6a = randn(1,Length6);
X6a = fftshift(abs(fft(x6a)));
FrequencyAxisX6a = -(Length6/2):(Length6/length(X6a)):((Length6/2)-(Length6/length(X6a)));

figure(3);
plot(FrequencyAxisX6a,X6a); 
title('Input'); ylabel('Amplitude');

%System 1
b1=[1 -0.4944 0.64];
a1=[1 -1.3335 0.49];
ab1 = inout(b1,a1,x6a,Length6);
AB1 = fftshift(abs(fft(ab1)));
FrequencyAxisAB1 = -(Length6/2):(Length6/length(AB1)):((Length6/2)-(Length6/length(AB1)));

%System 2
b2=[1 0.4944 0.64];
a2=[1 1.3335 0.49];
ab2 = inout(b2,a2,x6a,Length6);
AB2 = fftshift(abs(fft(ab2)));
FrequencyAxisAB2 = -(Length6/2):(Length6/length(AB2)):((Length6/2)-(Length6/length(AB2)));

figure(4);
subplot(2,1,1); 
plot(FrequencyAxisAB1,AB1);
title('Output Spectrum of System 1 (b1-a1)'); xlabel('Frequency'); ylabel('Amplitude');
subplot(2,1,2); 
plot(FrequencyAxisAB2,AB2); 
title('Output Spectrum of System 2 (b2-a2)'); xlabel('Frequency'); ylabel('Amplitude');

%6.B (Parallel System)
yparallel = ab1+ab2;
Yparallel = fftshift(abs(fft(yparallel)));
FrequencyAxisYparallel = -(Length6/2):(Length6/length(Yparallel)):((Length6/2)-(Length6/length(Yparallel)));

figure(5);
plot(FrequencyAxisYparallel,Yparallel); 
title('Output Spectrum of Parallel System (b1-a1 // b2-a2)'); xlabel('Frequency'); ylabel('Amplitude');

%6.C (Cascade System)
cascade = inout(b2,a2,ab1,Length6);
Cascade = fftshift(abs(fft(cascade)));
FrequencyAxisCascade = -(Length6/2):(Length6/length(Cascade)):((Length6/2)-(Length6/length(Cascade)));

figure(6);
plot(FrequencyAxisCascade,Cascade); 
title('Output Spectrum of Cascaded System (b1-a1 are cascaded b2-a2)'); xlabel('Frequency'); ylabel('Amplitude');

%% Question 7
%7.A
Exponential_a = [0.8*exp(1i*0.1*pi) 0.8*exp(-1i*0.1*pi)];
Poles_a = poly(Exponential_a);

figure(7); 
freqz(1,Poles_a,100);
title('Magnitude Response of the System (A)');

%7.B
Exponential_b = [0.8*exp(1i*0.5*pi) 0.8*exp(-1i*0.5*pi)];
Poles_b = poly(Exponential_b);

figure(8); 
freqz(1,Poles_b,100);
title('Magnitude Response of the System (B)');

%7.C
Exponential_c = [0.8*exp(1i*0.9*pi) 0.8*exp(-1i*0.9*pi)];
Poles_c = poly(Exponential_c);

figure(9); 
freqz(1,Poles_c,100);
title('Magnitude Response of the System (C)');

%7.D
Exponential_d = [0.1*exp(1i*0.5*pi) 0.1*exp(-1i*0.5*pi)];
Poles_d = poly(Exponential_d);

figure(10); 
freqz(1,Poles_d,100);
title('Magnitude Response of the System (D)');

%7.E
Exponential_e = [0.9*exp(1i*0.5*pi) 0.9*exp(-1i*0.5*pi)];
Poles_e = poly(Exponential_e);

figure(11); 
freqz(1,Poles_e,100);
title('Magnitude Response of the System (E)');

%% Question 8
%8.A
NumeratorA = [1 0.7264 0.64];
DenominatorA = [1 -0.6356 0.49];

figure(12);
subplot(2,2,[1,2]); 
zplane(NumeratorA,DenominatorA);
title('Pole-Zero Diagram Locations of System A');
subplot(2,2,3); 
impz(NumeratorA,DenominatorA,30);
title('Impulse Response of System A'); xlabel('n Samples'); ylabel('Amplitude');
subplot(2,2,4); 
stepz(NumeratorA,DenominatorA,30);
title('Unit Step Response of System A'); xlabel('n Samples'); ylabel('Amplitude');

%8.B
NumeratorB = [1 1.350 1.5625];
DenominatorB = [1 -0.6356 0.49];

figure(13);
subplot(2,2,[1,2]); 
zplane(NumeratorB,DenominatorB);
title('Pole-Zero Diagram Locations of System B');
subplot(2,2,3); 
impz(NumeratorB,DenominatorB,30);
title('Impulse Response of System B'); xlabel('n Samples'); ylabel('Amplitude');
subplot(2,2,4); 
stepz(NumeratorB,DenominatorB,30);
title('Unit Step Response of System B'); xlabel('n Samples'); ylabel('Amplitude');

%8.C
NumeratorC = [1 0.7264 0.64];
DenominatorC = [1 -1.3620 2.25];

figure(14);
subplot(2,2,[1,2]); 
zplane(NumeratorC,DenominatorC);
title('Pole-Zero Diagram Locations of System C');
subplot(2,2,3); 
impz(NumeratorC,DenominatorC,30);
title('Impulse Response of System C'); xlabel('n Samples'); ylabel('Amplitude');
subplot(2,2,4); 
stepz(NumeratorC,DenominatorC,30);
title('Unit Step Response of System C'); xlabel('n Samples'); ylabel('Amplitude');

%% Question 9
%9.A
figure(15);
freqz(NumeratorA,DenominatorA,100);
title('Magnitude&Phase Response of System A');
%9.B
figure(16);
freqz(NumeratorB,DenominatorB,100);
title('Magnitude&Phase Response of System B');
