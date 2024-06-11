#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;
struct SR_Vertex {
    float v[3];
    float uv[2];
};

struct SR_Triangle {
    int tv[3];
    float normals[3];
};

bool readPLY(const char* filename, SR_Vertex*& sr_verts, SR_Triangle*& tri_triags, int& noOfVertices, int& noOfFaces) {
    ifstream readIn(filename, ios::in);
    char line[256];
    readIn.getline(line, 256);

    // Read the header
    while (strcmp(line, "end_header") != 0) {
        stringstream ss;
        char elm[256];

        ss << line;
        ss >> elm;

        if (strcmp(elm, "element") == 0) {
            char next[10];
            ss >> next;
            if (strcmp(next, "vertex") == 0) {
                ss >> noOfVertices;
            } else if (strcmp(next, "face") == 0) {
                ss >> noOfFaces;
            } else {
                exit(0);
            }
        }
        readIn.getline(line, 256);
    }

    cout << "No-Of-Vertices: " << noOfVertices << " \nNo-Of-Faces: " << noOfFaces << endl;
    sr_verts = new SR_Vertex[noOfVertices];

    // Read the data
    int i;
    float dummy;
    for (i = 0; i < noOfVertices; i++) {
        readIn >> sr_verts[i].v[0];
        readIn >> sr_verts[i].v[1];
        readIn >> sr_verts[i].v[2];
        readIn >> dummy >> dummy >> dummy ;
        readIn >> sr_verts[i].uv[0];
        readIn >> sr_verts[i].uv[1];

        // use the line below to Read remaining dummy values
        //readIn >> dummy >> dummy >> dummy >> dummy >> dummy;
    }

    tri_triags = new SR_Triangle[noOfFaces];

    float x1, y1, z1;
    float x2, y2, z2;
    float x3, y3, z3;
    for (i = 0; i < noOfFaces; i++) {
        readIn >> dummy;
        readIn >> tri_triags[i].tv[0];
        readIn >> tri_triags[i].tv[1];
        readIn >> tri_triags[i].tv[2];

        // Calculate normals
        x1 = sr_verts[tri_triags[i].tv[0]].v[0];
        y1 = sr_verts[tri_triags[i].tv[0]].v[1];
        z1 = sr_verts[tri_triags[i].tv[0]].v[2];

        x2 = sr_verts[tri_triags[i].tv[1]].v[0];
        y2 = sr_verts[tri_triags[i].tv[1]].v[1];
        z2 = sr_verts[tri_triags[i].tv[1]].v[2];

        x3 = sr_verts[tri_triags[i].tv[2]].v[0];
        y3 = sr_verts[tri_triags[i].tv[2]].v[1];
        z3 = sr_verts[tri_triags[i].tv[2]].v[2];

        float coord1[3] = {x1, y1, z1};
        float coord2[3] = {x2, y2, z2};
        float coord3[3] = {x3, y3, z3};

        // Calculate normals here

        // Read remaining dummy values
        //readIn >> dummy >> dummy;
    }

    return true;
}

bool writePLY(const char* filename, const SR_Vertex* sr_verts, const SR_Triangle* tri_triags, int noOfVertices, int noOfFaces) {
    ofstream writeOut(filename, ios::out);
    if (!writeOut) {
        cerr << "Failed to open file for writing: " << filename << endl;
        return false;
    }

    // Write header
    writeOut << "ply\n";
    writeOut << "format ascii 1.0\n";
    writeOut << "element vertex " << noOfVertices << '\n';
    writeOut << "property float x\n";
    writeOut << "property float y\n";
    writeOut << "property float z\n";
    writeOut << "property float u\n";
    writeOut << "property float v\n";
    writeOut << "element face " << noOfFaces << '\n';
    writeOut << "property list uchar int vertex_indices\n";
    writeOut << "end_header\n";

    // Write vertex data
    for (int i = 0; i < noOfVertices; i++) {
        writeOut << sr_verts[i].v[0] << ' ';
        writeOut << sr_verts[i].v[1] << ' ';
        writeOut << sr_verts[i].v[2] << ' ';
        writeOut << sr_verts[i].uv[0] << ' ';
        writeOut << sr_verts[i].uv[1] << '\n';
    }

    // Write face data
    for (int i = 0; i < noOfFaces; i++) {
        writeOut << "3 " << tri_triags[i].tv[0] << ' ';
        writeOut << tri_triags[i].tv[1] << ' ';
        writeOut << tri_triags[i].tv[2] << '\n';
    }

    writeOut.close();
    return true;
}

int main() {
    const char* inputFileName = "Star.ply";
    const char* outputFileName = "Star_clean.ply";
    SR_Vertex* sr_verts;
    SR_Triangle* tri_triags;
    int noOfVertices = 0;
    int noOfFaces = 0;

    if (readPLY(inputFileName, sr_verts, tri_triags, noOfVertices, noOfFaces)) {
        // Process the data or clean the .ply file

        // Write the cleaned data to a new .ply file
        if (writePLY(outputFileName, sr_verts, tri_triags, noOfVertices, noOfFaces)) {
            cout << "Data written to: " << outputFileName << endl;
        }
    }

    // Clean up the allocated memory
    delete[] sr_verts;
    delete[] tri_triags;

    return 0;
}
