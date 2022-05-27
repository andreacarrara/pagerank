# PageRank

Ranking webpages applying linear algebra: C implementation of Google's [PageRank](https://wikipedia.org/wiki/PageRank) algorithm.

## Example

In an interconnected web of pages, how can we meaningfully define and quantify the importance of any given page?
Let's walk through an example to better understand how the algorithm works.

Suppose we have the following web made of four pages linking each other:

<p align="center">
  <img src="assets/web-light.png#gh-light-mode-only" width="200px" />
  <img src="assets/web-dark.png#gh-dark-mode-only" width="200px" />
</p>

Loading it is as easy as:

```
Let's start by creating a model of the web.
How many pages does your web have? 4
How many links does page 1 have? 3
1. What page does page 1 link? 2
...
```

Every webpage must link at least another page and no webpage can link itself.

The score of any given page is derived from the links made to that webpage from other pages.
The web thus becomes a democracy where pages vote for the importance of other pages by linking to them.

Let's store our web in a link matrix where entry `(i, j)` represents a link from page `j` to page `i`:

<p align="center">
  <img src="assets/link-matrix-light.png#gh-light-mode-only" width="270px" />
  <img src="assets/link-matrix-dark.png#gh-dark-mode-only" width="270px" />
</p>

Non-zero entry `(i, j)` equals to `1` over the number of links of page `j`.
In this democracy of the web each page gets a total of one vote that is evenly divided up among all of its links.

This transforms the web ranking problem into the standard problem of finding an [eigenvector](https://wikipedia.org/wiki/Eigenvalues_and_eigenvectors) for a square matrix.
Applying the [power iteration](https://wikipedia.org/wiki/Power_iteration) method, we compute the score column as the limit of iterations

<p align="center">
  <img src="assets/iteration-light.png#gh-light-mode-only" width="270px" />
  <img src="assets/iteration-dark.png#gh-dark-mode-only" width="270px" />
</p>

where `S` is a column with all entries equal to `1` over the number of webpages, and `m` a real number between `0` and `1`.
`X` can be initialized as any column with positive components and norm equal to `1`.

Lastly, we print the results:

```
Here are the standings:
1. Page 1: 0.368150
2. Page 3: 0.287969
3. Page 4: 0.202081
4. Page 2: 0.141801
```

## Usage

Clone the repository and run:

```bash
$ gcc pagerank.c -lm -o pagerank
$ ./pagerank
```

## Resources

Project inspired by [this](https://rose-hulman.edu/~bryan/google.html) paper by Kurt Bryan and Tanye Leise.
Further information [here](https://youtube.com/playlist?list=PLLssT5z_DsK9JDLcT8T62VtzwyW9LNepV) from lecture 5 to 11.
