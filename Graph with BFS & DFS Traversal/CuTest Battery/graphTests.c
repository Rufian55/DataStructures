/* Author: Sean Moore
 * Oregon State University
 * Date: 5/19/2016
 */

#include "cutest/CuTest.h"
#include "deque.h"
#include "graph.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/*
 * Compares the output of DfsIterative with the output of DfsRecursive for every
 * pair of vertices in 10 random graphs.
 * @param test
 */
void testDfsIterative(CuTest* test) {
	printf("--- testing dfsIterative ---\n");
	const int N = 10;
	int testNum, i, j, expected, actual;
	for (testNum = 0; testNum < N; ++testNum) {
		Graph* g = randomGraph(N, N - 1);
		printf("\nGraph %d\n---\n", testNum);
		printGraph(g);
		for (i = 0; i < g->numVertices; ++i) {
			for (j = i; j < g->numVertices; ++j) {
				Vertex* source = &g->vertexSet[i];
				Vertex* destination = &g->vertexSet[j];
				expected = dfsRecursive(g, source, destination);
				actual = dfsIterative(g, source, destination);
				CuAssertIntEquals(test, expected, actual);
			}
		}
		freeGraph(g);
	}
	printf("\n");
}

/*
 * Compares the output of BfsIterative with the output of DfsRecursive for every
 * pair of vertices in 10 random graphs.
 * @param test
 */
void testBfsIterative(CuTest* test) {
	printf("--- testing bfsIterative ---\n");
	const int N = 10;
	for (int testNum = 0; testNum < N; ++testNum) {
		Graph* g = randomGraph(N, N - 1);
		printf("\nGraph %d\n---\n", testNum);
		printGraph(g);
		int i, j, expected, actual;
		for (i = 0; i < g->numVertices; ++i) {
			for (j = i; j < g->numVertices; ++j) {
				Vertex* source = &g->vertexSet[i];
				Vertex* destination = &g->vertexSet[j];
				expected = dfsRecursive(g, source, destination);
				actual = bfsIterative(g, source, destination);
				CuAssertIntEquals(test, expected, actual);
			}
		}
		freeGraph(g);
	}
	printf("\n");
}

CuSuite* getGraphTestSuite() {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, testDfsIterative);
	SUITE_ADD_TEST(suite, testBfsIterative);
	return suite;
}
