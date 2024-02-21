//
// Written by Carolina P. Nogueira 2016
// Refactored by Deutschmann 27.09.2021
//

#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>

#include "../IManager.h"
#include "BenchParser.hpp"

/**
 * \class CircuitToBDD
 *
 * \brief Class to convert circuits nodes into BDD nodes
 *
 *  Circuit nodes are generated by the class bench_circuit_manager.
 *
 * \authors {Carolina Nogueira, Lucas Deutschmann}
 *
 */
class CircuitToBDD {
 public:
  explicit CircuitToBDD(shared_ptr<ClassProject::IManager> BDD_manager_p);
  ~CircuitToBDD();

  /**
   * \brief Generates a BDD from the circuit nodes provided
   * \param Topologically sorted list containing the circuit nodes
   * \return none
   *
   *  Generates the calls to the BDD package in order to
   *   generate the BDD equivalent to the provided circuit.
   */
  void GenerateBDD(const std::list<circuit_node_t> &circuit,
                   const std::string &benchmark_file);

  /**
   * \brief Print the generated BDD in text and dot format
   * \param The set of output labels to print a BDD for
   * \return none
   */
  void PrintBDD(const std::set<label_t> &output_labels);

 private:
  std::unordered_map<unique_ID_t, ClassProject::Node>
      node_to_bdd_id;  ///< Mapping from circuit node's unique ID to its BDD ID
  std::unordered_map<label_t, ClassProject::Node>
      label_to_bdd_id;  ///< Mapping from node's label to its BDD ID

  shared_ptr<ClassProject::IManager> bdd_manager{};
  std::string result_dir;  ///< Directory where the results are stored

  std::set<ClassProject::Node> output_nodes;
  std::set<ClassProject::Node> output_vars;

  /**
   * \brief Returns the BDD_ID of the given circuit ID
   * \param circuit_node is unique_ID_t
   * \return ClassProject::Node
   *
   */
  ClassProject::Node findBddId(unique_ID_t circuit_node);

  /**
   * \brief Generates the BDD node equivalent to a variable with label "label".
   * \param label is label_t
   * \return ClassProject::Node
   *
   */
  ClassProject::Node InputGate(const label_t &label);

  /**
   * \brief Generates the BDD node equivalent to the NOT gate.
   * \param node is set_of_circuit_t containing the circuit ID of the gate to be
   * inverted. \return ClassProject::Node
   *
   */
  ClassProject::Node NotGate(const set_of_circuit_t &node);

  /**
   * \brief Generates the BDD node equivalent to the AND gate.
   * \param node is set_of_circuit_t containing the circuit IDs of the gates to
   * be used as input. \return ClassProject::Node
   *
   */
  ClassProject::Node AndGate(set_of_circuit_t inputNodes);

  /**
   * \brief Generates the BDD node equivalent to the OR gate.
   * \param node is set_of_circuit_t containing the circuit IDs of the gates to
   * be used as input. \return ClassProject::Node
   *
   */
  ClassProject::Node OrGate(set_of_circuit_t inputNodes);

  /**
   * \brief Generates the BDD node equivalent to the NAND gate.
   * \param node is set_of_circuit_t containing the circuit IDs of the gates to
   * be used as input. \return ClassProject::Node
   *
   */
  ClassProject::Node NandGate(set_of_circuit_t inputNodes);

  /**
   * \brief Generates the BDD node equivalent to the NOR gate.
   * \param node is set_of_circuit_t containing the circuit IDs of the gates to
   * be used as input. \return ClassProject::Node
   *
   */
  ClassProject::Node NorGate(set_of_circuit_t inputNodes);

  /**
   * \brief Generates the BDD node equivalent to the XOR gate.
   * \param node is set_of_circuit_t containing the circuit IDs of the gates to
   * be used as input. \return ClassProject::Node
   *
   */
  ClassProject::Node XorGate(set_of_circuit_t inputNodes);

  void dumpBddText(std::ostream &out);

  void dumpBddDot(std::ostream &out);
};