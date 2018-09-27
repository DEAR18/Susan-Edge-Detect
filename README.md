# SUSAN-Edge-Detect
This is a edge detector with SUSAN algorithm.

effect without non maximum suppression:
![](https://github.com/DEAR18/SUSAN-Edge-Detect/raw/master/effect/T_effect.png)<br>
effect with non maximum suppression:
![](https://github.com/DEAR18/SUSAN-Edge-Detect/raw/master/effect/T_effect2.png)<br>
effect without non maximum suppression:
![](https://github.com/DEAR18/SUSAN-Edge-Detect/raw/master/effect/lena_effect.png)<br>
effect with non maximum suppression:
![](https://github.com/DEAR18/SUSAN-Edge-Detect/raw/master/effect/lena_effect2.png)<br>

## 1. Prerequisites
1.1 opencv library

## 2. Summary of SUSAN algorithm
The following summary is copied from [here](https://users.fmrib.ox.ac.uk/~steve/susan/susan/node6.html), you can also see more details about this algorithom from it.

2.1 Place a circular mask around the pixel in question (the nucleus).<br>
2.2 Calculate the number of pixels within the circular mask which have similar brightness to the nucleus. (These pixels define the USAN.)<br>
2.3 Subtract the USAN size from the geometric threshold to produce an edge strength image.<br>
2.4 Use moment calculations applied to the USAN to find the edge direction.<br>
2.5 Apply non-maximum suppression, thinning and sub-pixel estimation, if required.<br>

## 3. Others
The effect seems not to be the best. I will updata the effect image after the code being improved.
