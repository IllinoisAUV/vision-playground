J = imread('red_init.jpg');
grey = rgb2gray(J);
grey = double(grey);
[px,py] = gradient(grey);

disp(px);
disp(py);
disp(grey);

thres = 0;
px_idx = find(abs(px)<thres);
py_idx = find(abs(py)<thres);
px(px_idx) = 0;
py(px_idx) = 0;

figure;
quiver(px,py);