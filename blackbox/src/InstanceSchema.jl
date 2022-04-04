json_instance_schema_string = """{
      "\$schema": "http://json-schema.org/draft-06/schema#",
      "\$ref": "#/definitions/Instance",
      "definitions": {
          "Instance": {
              "type": "object",
              "additionalProperties": false,
              "properties": {
                  "quant_dias": {
                      "type": "integer"
                  },
                  "quant_horarios": {
                      "type": "integer"
                  },
                  "quant_workspace": {
                      "type": "integer"
                  },
                  "infos": {
                      "type": "array",
                      "items": {
                          "\$ref": "#/definitions/Info"
                      }
                  }
              },
              "required": [
                  "infos",
                  "quant_dias",
                  "quant_horarios",
                  "quant_workspace"
              ],
              "title": "Instance"
          },
          "Info": {
              "type": "object",
              "additionalProperties": false,
              "properties": {
                  "nome": {
                      "type": "string"
                  },
                  "horarios": {
                      "\$ref": "#/definitions/Horarios"
                  },
                  "quantidade_minima": {
                      "type": "integer"
                  }
              },
              "required": [
                  "horarios",
                  "nome",
                  "quantidade_minima"
              ],
              "title": "Info"
          },
          "Horarios": {
              "type": "object",
              "additionalProperties": false,
              "properties": {
                  "segunda": {
                      "type": "array",
                      "items": {
                          "type": "integer"
                      }
                  },
                  "terca": {
                      "type": "array",
                      "items": {
                          "type": "integer"
                      }
                  },
                  "quarta": {
                      "type": "array",
                      "items": {
                          "type": "integer"
                      }
                  },
                  "quinta": {
                      "type": "array",
                      "items": {
                          "type": "integer"
                      }
                  },
                  "sexta": {
                      "type": "array",
                      "items": {
                          "type": "integer"
                      }
                  }
              },
              "required": [
                  "segunda",
                  "terca",
                  "quarta",
                  "quinta",
                  "sexta"
              ],
              "title": "Horarios"
          }
      }
  }"""

instance_schema_validator = JSONSchema.Schema(json_instance_schema_string)