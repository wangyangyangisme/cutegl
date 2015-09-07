#ifndef MESH_H
#define MESH_H

#include <QImage>
#include <QMatrix4x4>
#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include <mesh.h>
#include <vertex.h>

class QOpenGLShaderProgram;
class QOpenGLTexture;
namespace cgl {
class Mesh : public QObject
{
    Q_OBJECT

public:
    Mesh(QObject *parent = 0);
    ~Mesh();

    void                   bind();
    void                   create();
    bool                   hasIndices() const { return mIndices.isEmpty(); }
    int                    indicesCount() const { return mIndices.count(); }
    GLenum                 mode() const { return mMode; }
    QMatrix4x4             modelMatrix() const { return mModelMatrix; }
    void                   release();
    void                   rotate(float angle, float x, float y, float z) { mModelMatrix.rotate(angle, x, y, z); }
    void                   setDefaultShaders();
    void                   setTextureImage(const QString filename) {setTextureImage(QImage(filename));}
    void                   setTextureImage(const QImage &image);
    QOpenGLShaderProgram   *shaderProgram() const { return mShaderProgram; }
    void                   translate(float x, float y, float z) { mModelMatrix.translate(x, y, z); }
    Vertex&                vertex(int index){ return mVertices[index];}
    int                    verticesCount() const { return mVertices.count(); }
    QVector<Vertex>        vertices() const { return mVertices; }

protected:
    void                   addVertex(const Vertex &ver) { mVertices.append(ver); }
    void                   addVertex(const QVector<Vertex>& ver) {mVertices.append(ver);}
    void                   clearVertices(){mVertices.clear();}
    virtual void           makeMesh() = 0;
    void                   resetTransform() { mModelMatrix.setToIdentity(); }
    void                   scale(float x, float y, float z) {mModelMatrix.scale(x,y,z);}
    void                   scale(float f) { mModelMatrix.scale(f);}
    void                   setShaders(const QString &vertexFile, const QString &fragmentFile);
    void                   setMode(GLenum mode) { mMode = mode;}
    QImage                 textureImage() const { return mTextureImage; }

private:
    QOpenGLBuffer            mIndexBuffer;      // the indexes to the verices in graphic card
    QVector<GLuint>          mIndices;          // the indices list
    GLenum                   mMode;             // drawing mode to connect vertices
    QMatrix4x4               mModelMatrix;      // the model matrix
    QOpenGLShaderProgram     *mShaderProgram;   // the shadder program
    QOpenGLTexture           *mTexture;         // texture od the mesh
    QImage                   mTextureImage;    // image of the texture
    QOpenGLVertexArrayObject mVao;              // the array ....
    QOpenGLBuffer            mVertexBuffer;     // the buffer that holds the lis of vertices in graphic card
    QVector<Vertex>          mVertices;         // list of vertexes for this mesh
};
}
#endif // MESH_H
