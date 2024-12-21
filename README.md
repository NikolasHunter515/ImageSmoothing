<h1>Image Smoothing: Noise Removal</h1>
<h3>Setup:</>
For the code to work an image must be converted from a jpg to a pgm. It will still work if converted from a different file format, but the result will be darker; as pixel values will be out of the 0 - 255 range.
Note* The code as of now(12/11/24) is not capable of handeling colored images.
After converting to a pgm, convert the same file to a txt file.

<h3>Method usage:</>
When calling the medianFilter or massFiltering pass file names without extension.

I also advise to not add additional noise to older images. As they typically already have noise.

Window size - For best results use a window size of 3. Larger sizes will slow down program and produce blurry images.

Median algorithm - Current filerting method uses random median, which produced faster result compared to the median of medians. Why did this work? When randomly selecting a median(pivot) there is a 1 / n!
chance of selecting the worse possible median.

<h3>Program Results:</h3>
If your machine does not have software to view pgm files, here is a helpful tool to view <a href = "https://kylepaulsen.com/stuff/NetpbmViewer/">pgm's</a>.
