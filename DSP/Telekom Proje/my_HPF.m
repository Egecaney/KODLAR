function [y] = my_HPF(x,fs,fcut)

hPassSpecs = fdesign.highpass('N,F3db',10,fcut,fs);
highPass_filter = design(hPassSpecs,'butter');
y = filter(highPass_filter,x);

end