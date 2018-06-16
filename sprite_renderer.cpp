#include "sprite_renderer.h"


SpriteRenderer::SpriteRenderer(Shader &shader, int type)
{
    this->shader = shader;
    if (type == 2)
        this->initRenderData();
    else if (type == 3)
        this->initRenderData3d();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color)
{
    // Prepare transformations
    this->shader.Use();
    glm::mat4 model;
    // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
    model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
    model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

    this->shader.SetMatrix4("model", model);
    // Render textured quad
    this->shader.SetVector3f("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

// for render 3d scene
void SpriteRenderer::DrawSprite(Texture2D &texture, glm::vec3 position, glm::vec2 size, GLfloat rotate, glm::vec3 axis, glm::mat4 view, glm::mat4 proj, glm::vec3 color)
{
    // Prepare transformations
    this->shader.Use();
    // glm::mat4 model;
    // // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
    // model = glm::translate(model, position);
    // model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
    // model = glm::rotate(model, rotate, axis); // Then rotate
    // model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back
    // model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

    // glm::mat4 mvp = proj * view * model;
    glm::mat4 mvp = proj * view;
    this->shader.SetMatrix4("mvp", mvp);
    // Render textured quad
    this->shader.SetVector3f("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}


void SpriteRenderer::initRenderData()
{
    // Configure VAO/VBO
    GLuint VBO;
    GLfloat vertices[] = {
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::initRenderData3d()
{
    // Configure VAO/VBO
    GLuint VBO;
    GLfloat vertices[] = {
        // Pos            // Tex
        // 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        // 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        // 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

        // 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        // 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        // 1.0f, 0.0f, 0.0f, 1.0f, 0.0f

        // works
        // 0.0f, -0.5f, 1.0f, 0.0f, 1.0f,
        // 1.0f, -0.5f, 0.0f, 1.0f, 0.0f,
        // 0.0f, -0.5f, 0.0f, 0.0f, 0.0f,

        // 0.0f, -0.5f, 1.0f, 0.0f, 1.0f,
        // 1.0f, -0.5f, 1.0f, 1.0f, 1.0f,
        // 1.0f, -0.5f, 0.0f, 1.0f, 0.0f

        0.0f, -0.5f, 20.0f, 0.0f, 20.0f,
        20.0f, -0.5f, 0.0f, 20.0f, 0.0f,
        0.0f, -0.5f, 0.0f, 0.0f, 0.0f,

        0.0f, -0.5f, 20.0f, 0.0f, 20.0f,
        20.0f, -0.5f, 20.0f, 20.0f, 20.0f,
        20.0f, -0.5f, 0.0f, 20.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
