//Grade report project.
//Author:       Ryan Wagner
//Date:         August 24, 2014
//Description:  Grade report project for reddit.com/dailyprogrammer #167.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stud{
  char first[ 30 ], last[ 30 ];
  int score[ 5 ];
  double avg;
  char * grade;
  struct stud * next;
};

struct stud * insert ( struct stud * root, struct stud * node ){
  if ( root == 0 ){
    root = node;
    root->next = 0;
  }
  else if ( node->avg >= root->avg ){
    node->next = root;
    root = node;
  }
  else{
    struct stud * curr = root;
    while( node->avg < curr->next->avg ){
      curr = curr->next;
    }
    while( node->avg == curr->next->avg && 
        strcmp( node->last, curr->next->last ) > 0 ){
      curr = curr->next;
    }
    node->next = curr->next;
    curr->next = node;
  }
  return root;
}

char * calc( struct stud * node ){
   if( node->avg >= 98 )
    return "A+";
   if( node->avg >= 93 )
    return "A";
   if( node->avg >= 90 )
    return "A-";
   if( node->avg >= 87 )
    return "B+";
   if( node->avg >= 83 )
    return "B";
   if( node->avg >= 80 )
    return "B-";
   if( node->avg >= 77 )
    return "C+";
   if( node->avg >= 73 )
    return "C";
   if( node->avg >= 70 )
    return "C-";
   if( node->avg >= 67 )
    return "D+";
   if( node->avg >= 63 )
    return "D";
   if( node->avg >= 60 )
    return "D-";
   return "F"; 
}

int main( void ){
  FILE * in = fopen( "input.dat", "r" );
  struct stud * root = ( struct stud * )malloc( sizeof( struct stud ) );
  char list[ 150 ];
  while( fgets( list, 150, in ) ){
    struct stud * node = ( struct stud * )malloc( sizeof( struct stud ) );
    sscanf( list,
        "%15[^,]%*[^ABCDEFGHIJKLMNOPQRSTUVWXYZ]%15[^0123456789]%d%d%d%d%d",
        node->first, node->last, node->score, &node->score[ 1 ],
        &node->score[ 2 ], &node->score[ 3 ], &node->score[ 4 ]);
    node->avg = ( node->score[ 0 ] + node->score[ 1 ] + node->score[ 2 ] +
        node->score[ 3 ] + node->score[ 4 ] ) / 5;
    node->grade = calc( node );
    root = insert( root, node );
  }
  ( void )printf( "%-15s%-15s%-6s%5s%5s%5s%5s%5s%5s\n", "First",
      "Last", "Grade", "Pct.", "T1", "T2", "T3", "T4", "T5" );
  while( root->next != 0 ){
    ( void )printf( "%-15s%-15s%-6s%5.1lf%5d%5d%5d%5d%5d\n", root->first,
        root->last, root->grade, root->avg, root->score[ 0 ],
        root->score[ 1 ],root->score[ 2 ],root->score[ 3 ],root->score[ 4 ] );
    root = root->next;
  }
  fclose( in );
}
