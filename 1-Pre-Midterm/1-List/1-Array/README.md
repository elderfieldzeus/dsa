# List Array Implementation

### Main Difference:

**Version One** (List is a structure containing an array and variable count):
```
typedef struct {
    int data;
} Element;

typedef struct {
    Element Elements[MAX];
    int count;
} Version_One;
```
<br />

**Version Two** (List is a pointer to a structure containing an array and variable count):
```
typedef struct {
    int data;
} Element;

typedef struct node {
    Element Elements[MAX];
    int count;
} *Version_Two;
```

<br />

**Version Three** (List is a structure containing a pointer to the 1st element of a dynamic array, and variable count):
```
typedef struct {
    int data;
} Element;

typedef struct {
    Element *Elements; //assuming MAX is defined
    int count;
} Version_Three;
```

<br />

**Version Four** (List is a pointer to a structure containing a pointer to the 1st element of a dynamic array, and variable count):
```
typedef struct {
    int data;
} Element;

typedef struct node {
    Element *Elements; //assuming MAX is defined
    int count;
} *Version_Four;
```