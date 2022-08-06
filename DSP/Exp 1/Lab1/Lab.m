%% Question 1

[x,fs] = audioread('sound1.wav');
X = fftshift(abs(fft(x)));
FrequencyAxis = (-fs/2):(fs/length(X)):(fs/2 - fs/length(X));
f_x = linspace(-5512,5512,2800);

figure;
stem(f_x,X);

%% Question 2
figure;
stem(x);
y = downxx(x,2);
X=fftshift(abs(fft(x)));
figure;
stem(X);    
Y=fftshift(abs(fft(y)));
figure;stem(Y); 
   
%% Question 3
[z1,fs1]=wavread('sound1.wav');
[z2,fs2]=wavread('sound1.wav');
f_z=linspace(-5512,5512,2800);
 
z=z1+z2;

Z1=fftshift(abs(fft(z1)));
Z2=fftshift(abs(fft(z2)));
Z=fftshift(abs(fft(z)));
figure;stem(f_z,Z1);
figure;stem(f_z,Z2);
figure;stem(f_z,Z);
 
sound(z1);
sound(z2);
sound(z);