# SUSAN-Edge-Detect
This is a edge detector with SUSAN algorithm.

# 1. Prerequisites
1.1 opencv library

# 2. Summary of SUSAN algorithm
The following summary is copied from here, you can also see more detail about this algorithom from it.

1.1 Place a circular mask around the pixel in question (the nucleus)./n
1.2 Calculate the number of pixels within the circular mask which have similar brightness to the nucleus. (These pixels define the USAN.)
1.3 Subtract the USAN size from the geometric threshold to produce an edge strength image.
1.4 Use moment calculations applied to the USAN to find the edge direction.
1.5 Apply non-maximum suppression, thinning and sub-pixel estimation, if required.
