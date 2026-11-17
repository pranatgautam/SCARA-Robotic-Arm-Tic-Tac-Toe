clc, clear, close all
% Read the binary data from the .rgb565 file
fileID = fopen('arial_image.rgb', 'r');
rawData = fread(fileID, inf, 'uint16');
fclose(fileID);

w = 240;
h = 240;
rawData = swapbytes(uint16(reshape(rawData, [w h] )'));
% Extract red, green, and blue channels
red = uint8(bitshift(bitand(rawData, 0xF800), -8));
green = uint8(bitshift(bitand(rawData, 0x07E0), -3));
blue = uint8(bitshift(bitand(rawData, 0x001F), 3));


% % Reshape the channels to form an RGB image
% red = reshape(red, [width_of_image, height_of_image]);
% green = reshape(green, [width_of_image, height_of_image]);
% blue = reshape(blue, [width_of_image, height_of_image]);

% Concatenate the channels to form the RGB image
rgbImage = cat(3, red, green, blue);
size(rgbImage);
% Display the image
imshow(rgbImage);