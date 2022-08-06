%% Question 1
h = fir1(30,0.3,'low',hamming(31));

%% Question 2
% 2.A
% function y = mycir(x,h,N)
% L_x = length(x);
% L_h = length(h);
% zero padding
% x = [x,zeros(1,N - L_x)];
% h_zp = [h, zeros(1,N-L_h)];
% h_r = [h(1), fliplr(h_zp(2:end))];
% toe = toeplitz(h_r,h_zp);
% y = x*toe;
% end

% 2.B
% function y = dft(x,h,N)
% X = fft(x,N);
% H = fft(h,N);
% Y = X.*H;
% y = ifft(Y,N);
%end

%% Question 3
[s1_6, Fs] = audioread('S1_6.wav');
%length(s1_6) = 3500 , length(h) = 31;................. 3530
y1 = mycir(s1_6',h,3530);
y2 = dft(s1_6',h,3530);

Y1 = fftshift(abs(fft(y1)));
freqY1 = linspace(-1,1-1/length(Y1),length(Y1));

Y2 = fftshift(abs(fft(y2)));
freqY2 = linspace(-1,1-1/length(Y2),length(Y2));

figure(1);
subplot(2,2,1);
plot(y1); title('Waveform of y1'); xlabel('Samples'); ylabel('Amplitude');
subplot(2,2,2);
plot(y2); title('Waveform of y2'); xlabel('Samples'); ylabel('Amplitude');   
subplot(2,2,3);
plot(freqY1,Y1); title('Spectrum y1'); xlabel('Normalized Frequency'); ylabel('Magnitude');  
subplot(2,2,4);
plot(freqY2,Y2); title('Spectrum of y2'); xlabel('Normalized Frequency'); ylabel('Magnitude');   

% Comment 
% Our signals lenght is 3500 and our filters lenght is 31.
% If N is greater than L+P-1 lineer conv. is equal to circular conv. and if N is less there is alliasing.
% So N must be greater than 3500.y1 and y2 is same signal, my both 2 filter gives us same results.

%% Question 4

% function [y]=overlapsave_dft(x,h,L)
% P=length(h);
% N=length(x);
% x=[zeros(1,P-1) x]; % zero padding(length of P)
% num_b=length(x)/(L-P); % to calculate how many blocks are there
% x=[x zeros(1,5*(L-P))];
% y=[];% in order to use as input below
% for i=0:num_b;
% temp=dft(x((L-P)*i+1:(L-P)*i+L),h,L);
% y=cat(2,y,temp(P+1:end)); %combine y and dft result of new block
% end
% y=datawrap(y,N+P-1);
% end

%% Question 5

% function [y] = overlapadd_cir(x,h,L)
% N = length(x);
% P = length(h);
% M = N / L ;
% y = conv(x(1:L),h);
% w = [y((L+1):(L+P-1))]; 
% w(P:L) = 0;
% for counter = 2:M
%     index = (counter - 1) * L + 1;
%     z = conv(x(index:(index+L-1)),h); 
%     y(index:(index+L-1)) = z(1:L) + w(1:L);
%     w = [z((L+1):(L+P-1))] ;
%     w(P:L) = 0;
% end

%% Question 6
[s2_6, Fs] = audioread('S2_6.wav');

y3=overlapadd_cir(s2_6',h,256);
y4=overlapsave_dft(s2_6',h,227);
y5 = conv(s2_6',h);

Y3=fftshift(abs(fft(y3)));
freqY3 = linspace(-1,1-1/length(Y3),length(Y3));
Y4=fftshift(abs(fft(y4)));
freqY4 = linspace(-1,1-1/length(Y4),length(Y4));
Y5=fftshift(abs(fft(y5)));
freqY5 = linspace(-1,1-1/length(Y5),length(Y5));

figure(2);
subplot(3,1,1);
plot(y3); title('Waveform of y3'); xlabel('Samples'); ylabel('Amplitude');
subplot(3,1,2);
plot(y4); title('Waveform of y4'); xlabel('Samples'); ylabel('Amplitude');
subplot(3,1,3);
plot(y5); title('Waveform of y5'); xlabel('Samples'); ylabel('Amplitude');

figure(3);
subplot(3,1,1); 
plot(freqY3,Y3); title('Spectrum of y3'); xlabel('Normalized Frequency'); ylabel('Magnitude');  
subplot(3,1,2);  
plot(freqY4,Y4); title('Spectrum of y4'); xlabel('Normalized Frequency'); ylabel('Magnitude');  
subplot(3,1,3); 
plot(freqY5,Y5); title('Spectrum of y5'); xlabel('Normalized Frequency'); ylabel('Magnitude');  


