#include "renderer.h"

void Renderer::draw(Shader &shader, VertexArray &vao, GLint first, GLsizei count) {
    shader.use();
    vao.bind();
    GlCall(glDrawArrays(GL_TRIANGLES, first, count));
}
void Renderer::draw(Shader &shader, ElementBuffer &vao, GLsizei count) {
    shader.use();
    vao.bind();
    GlCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0));
}
void Renderer::clear() {
    GlCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
    GlCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
void Renderer::drawGrid(int numbers, Shader &shader, VertexArray &vao, glm::mat4 &projection, glm::mat4 &view) {
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    shader.setVec4("color", 1.0, 1.0, 1.0, 0.3);
    shader.use();
    for (int i = -numbers; i < numbers + 1; i++) {
        glm::mat4 model{1.0f};
        model = glm::scale(model, glm::vec3(1.0 * numbers, 1.0, 1.0));
        model = glm::translate(model, glm::vec3(0.0, 0.0, 1.0 * i));
        shader.setMat4("model", model);
        vao.bind();
        GlCall(glDrawArrays(GL_LINES, 0, 6));
        model = glm::mat4{1.0f};
        model = glm::translate(model, glm::vec3(1.0 * i, 0.0, 0.0));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
        model = glm::scale(model, glm::vec3(1.0 * numbers, 1.0, 1.0));
        shader.setMat4("model", model);
        vao.bind();
        GlCall(glDrawArrays(GL_LINES, 0, 6));
    }
}