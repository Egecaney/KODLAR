% Egemen Can Ayduðan - 21728036
% Preliminary Work 6

h1 = fir1(50,0.2,'low');

%% Question 3
n = 0:255;
x1 = cos(0.1*pi*n)+cos(0.3*pi*n)+cos(0.5*pi*n)+cos(0.7*pi*n)+cos(0.9*pi*n);

%% Question 4&5
% 4.A
y = conv(x1,h1);
Y = fftshift(abs(fft(y)));
FreqAxisY = linspace(-1,1,length(Y));
% 4.B
y1 = dftfilt(x1,h1,256);
Y1 = fftshift(abs(fft(y1)));
FreqAxisY1 = linspace(-1,1,length(Y1));
% 4.C
y2 = convfilt(x1,h1,256);
Y2 = fftshift(abs(fft(y2)));
FreqAxisY2 = linspace(-1,1,length(Y2));
% 4.D
y3 = dftfilt(x1,h1,512);
Y3 = fftshift(abs(fft(y3)));
FreqAxisY3 = linspace(-1,1,length(Y3));
% 4.E
y4 = convfilt(x1,h1,512);
Y4 = fftshift(abs(fft(y4)));
FreqAxisY4 = linspace(-1,1,length(Y4));

figure(1);
subplot(5,2,1); 
plot(y); xlabel('Samples'); ylabel('Amplitude'); title('Filtered Signal y[n]');
subplot(5,2,2); 
plot(FreqAxisY,Y); xlabel('Normalized Frequency'); ylabel('Amplitude'); title('Magnitude Spectrum of y[n]');
subplot(5,2,3); 
plot(y1); xlabel('Samples'); ylabel('Amplitude'); title('Filtered Signal y_1[n]');
subplot(5,2,4); 
plot(FreqAxisY1,Y1); xlabel('Normalized Frequency'); ylabel('Amplitude'); title('Magnitude Spectrum of y_1[n]');
subplot(5,2,5); 
plot(y2); xlabel('Samples'); ylabel('Amplitude'); title('Filtered Signal y_2[n]');
subplot(5,2,6); 
plot(FreqAxisY2,Y2); xlabel('Normalized Frequency'); ylabel('Amplitude'); title('Magnitude Spectrum of y_2[n]');
subplot(5,2,7); 
plot(y3); xlabel('Samples'); ylabel('Amplitude'); title('Filtered Signal y_3[n]');
subplot(5,2,8); 
plot(FreqAxisY3,Y3); xlabel('Normalized Frequency'); ylabel('Amplitude'); title('Magnitude Spectrum of y_3[n]');
subplot(5,2,9); 
plot(y4); xlabel('Samples'); ylabel('Amplitude'); title('Filtered Signal y_4[n]');
subplot(5,2,10); 
plot(FreqAxisY4,Y4); xlabel('Normalized Frequency'); ylabel('Amplitude'); title('Magnitude Spectrum of y_4[n]');

%% Question 6
[Sound,FSound] = audioread('sound.wav');
SOUND = fftshift(abs(fft(Sound)));
FreqAxisSound = linspace(-1,1,length(SOUND));

Output1 = dftfilt(Sound',h1,(length(h1)+length(Sound)-1));
OUTPUT1  = fftshift(abs(fft(Output1)));
FreqAxisOutput = linspace(-1,1,length(OUTPUT1));

TimeInput = (0:length(Sound)-1)*(1/FSound);
TimeOutput = (0:length(Output1)-1)*(1/FSound);

figure(2);
subplot(4,1,1); 
plot(TimeInput,Sound); xlabel('Time (s)'); ylabel('Amplitude'); title('Sound Signal')
subplot(4,1,3); 
plot(FreqAxisSound,SOUND); xlabel('Normalized Frequency'); ylabel('Amplitude'); title('Magnitude Spectrum of Sound Signal')
subplot(4,1,2); 
plot(TimeOutput,Output1); xlabel('Time (s)'); ylabel('Amplitude'); title('Output Signal')
subplot(4,1,4); 
plot(FreqAxisOutput,OUTPUT1); xlabel('Normalized Frequency'); ylabel('Amplitude'); title('Magnitude Spectrum of Output Signal (with dftfilt)')

%% Question 7
Output2 = convsave(Sound,h1,100);
OUTPUT2 = fftshift(abs(fft(Output2)));
FreqAxisOutput2 = linspace(-1,1,length(OUTPUT2));

figure(3);
subplot(4,1,1); 
plot(TimeInput,Sound); xlabel('Time (s)'); ylabel('Amplitude'); title('Sound')
subplot(4,1,3); 
plot(FreqAxisSound,SOUND); xlabel('Normalized Frequency'); ylabel('Amplitude'); title('Magnitude Spectrum of Sound Signal')
subplot(4,1,2); 
plot(TimeInput,Output2); xlabel('Time (s)'); ylabel('Amplitude'); title('Output2 Signal')
subplot(4,1,4); 
plot(FreqAxisOutput2,OUTPUT2); xlabel('Normalized Frequency'); ylabel('Amplitude'); title('Magnitude Spectrum of Output2 Signal (overlap save - circular conv.)')

%% Question 8
Output3 = dftsave(Sound,h1,100);
OUTPUT3 = fftshift(abs(fft(Output3)));
FreqAxisOutput3 = linspace(-1,1,length(OUTPUT3));

figure(4);
subplot(4,1,1); 
plot(TimeInput,Sound); xlabel('Time (s)'); ylabel('Amplitude'); title('Sound')
subplot(4,1,3); 
plot(FreqAxisSound,SOUND/length(SOUND)); xlabel('Normalized Frequency'); ylabel('Amplitude'); title('Magnitude Spectrum of Sound Signal')
subplot(4,1,2); 
plot(TimeInput,Output3); xlabel('Time (s)'); ylabel('Amplitude'); title('Output3 Signal')
subplot(4,1,4); 
plot(FreqAxisOutput3,OUTPUT3/length(OUTPUT3)); xlabel('Normalized Frequency'); ylabel('Amplitude'); title('Magnitude Spectrum of Output3 Signal (overlap save - DFT)')

%% Question 10
OutputLast = convadd(Sound,h1,100);
SoundLenght = length(Sound);
TimeAxisSound = (0:SoundLenght-1)*(1/FSound);

[X,~] = freqz(Sound);
[OUTPUTLAST,~]= freqz(OutputLast);
X = [flipud(X);X];
OUTPUTLAST = [flipud(OUTPUTLAST);OUTPUTLAST];
FreqAxisX = linspace(-1,1,length(X));

OutputLast = dftadd(Sound,h1,100);
[X,wx] = freqz(Sound);
[OUTPUTLAST,wo] = freqz(OutputLast);
X = [flipud(X);X];
OUTPUTLAST = [flipud(OUTPUTLAST);OUTPUTLAST];
FreqAxisX = linspace(-1,1,length(X));

figure(5);
subplot(6,1,1); 
plot(TimeAxisSound,Sound); title('Sound Signal'); xlabel('Time (s)'); ylabel('Amplitude');
subplot(6,1,2); 
plot(FreqAxisX,abs(X)/SoundLenght); title('Magnitude Spectrum of Sound Signal'); xlabel('Normalized Frequency'); ylabel('Amplitude');
subplot(6,1,3); 
plot(TimeAxisSound,OutputLast); title('Output Signal (overlap add - convolution)');xlabel('Time (s)'); ylabel('Amplitude');
subplot(6,1,4); 
plot(FreqAxisX,abs(OUTPUTLAST)/SoundLenght); title('Magnitude Spectrum of Output (overlap add - convolution)'); xlabel('Normalized Frequency'); ylabel('Amplitude');
subplot(6,1,5); 
plot(TimeAxisSound,OutputLast); title('Output Signal (overlap add - DFT)'); xlabel('Time (s)'); ylabel('Amplitude');
subplot(6,1,6); 
plot(FreqAxisX,abs(OUTPUTLAST)/SoundLenght); title('Magnitude Spectrum of Output (overlap add - DFT)'); xlabel('Normalized Frequency'); ylabel('Amplitude');
