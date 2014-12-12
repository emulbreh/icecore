#ifndef IC_VERSIONINDEX_H
#define IC_VERSIONINDEX_H

#include <stdint.h>
#include <string.h>

#include "document.h"
#include "cursor.h"


#define INDEX_NODE_BITS 1
#define INDEX_NODE_SIZE (1 << INDEX_NODE_BITS)


typedef enum {
    OK = 0,
    DOCUMENT_DOES_NOT_EXIST,
    VERSION_DOES_NOT_EXIST,
    VERSION_SKIPPED,
} IndexError;


typedef struct IndexNode{
    Version version;
    struct IndexNode* children[INDEX_NODE_SIZE];
} IndexNode;

typedef struct{
    Version version;
    IndexNode* root;
    unsigned int depth;
} Tree;


typedef struct {
    Version last_version;
    Tree** trees;
} DocumentVersionIndex;


Tree* tree_create(Version version, Tree* base);
size_t tree_capacity(Tree* tree);
void tree_insert(Tree* tree, Id id, Document* value);
IndexError tree_get(Tree* tree, Id id, Document** value);
void tree_delete(Tree* tree);
size_t tree_size(Tree* tree);
void tree_dump(Tree* tree);

DocumentVersionIndex* versionindex_create();
IndexError versionindex_insert(DocumentVersionIndex* idx, Id id, Version version, Document* value);
IndexError versionindex_get(DocumentVersionIndex* idx, Id id, Version version, Document** value);
size_t versionindex_size(DocumentVersionIndex* idx);
void versionindex_delete(DocumentVersionIndex* idx);
Cursor* versionindex_cursor(DocumentVersionIndex* idx, Version version);

#endif