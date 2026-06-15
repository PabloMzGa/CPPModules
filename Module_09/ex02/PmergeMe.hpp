/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 18:25:21 by pablo             #+#    #+#             */
/*   Updated: 2026/06/16 00:07:09 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <ctime>
#include <deque>
#include <limits>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <cassert>
#include <iostream>
#include <sstream>

class PmergeMe
{
  public:
	PmergeMe();
	PmergeMe(const PmergeMe &src);
	PmergeMe(const std::string &input);
	PmergeMe &operator=(const PmergeMe &src);
	~PmergeMe();
	void sort();

  private:
	static unsigned int parse_positive_int(const std::string &token);
	template <typename Container> static bool is_sorted(const Container &src);
	template <typename Container>
	static void load_values(const std::string &input, Container &container);
	template <typename Container>
	static void apply_order(Container &cont,
	                        typename Container::iterator *it_array);

	std::vector<unsigned int> _vector;
	std::deque<unsigned int> _deque;

	double _vector_time_ms;
	double _deque_time_ms;
};

template <typename Container>
void PmergeMe::load_values(const std::string &input, Container &container)
{
	unsigned int value;

	std::stringstream ss(input);
	std::string token;
	while (ss >> token)
	{
		value = parse_positive_int(token);
		container.push_back(value);
	}
	if (container.empty())
		throw std::runtime_error("Error: no numbers provided");
}

template <typename Container> bool PmergeMe::is_sorted(const Container &src)
{
	if (src.size() <= 1)
		return (true);
	typename Container::const_iterator it = src.begin();
	typename Container::const_iterator prev = it;
	++it;
	for (; it != src.end(); ++it, ++prev)
	{
		if (*prev > *it)
			return (false);
	}
	return (true);
}

template <typename Container>
void PmergeMe::apply_order(Container &cont,
                           typename Container::iterator *it_array)
{
	Container tmp; // Crea un contenedor temporal vacío

	// Copiamos los valores en el orden indicado por it_array
	std::size_t n = cont.size();
	for (std::size_t i = 0; i < n; ++i)
		tmp.push_back(*it_array[i]);

	// Sustituimos el contenedor original por el ordenado
	cont = tmp;
	delete[] it_array;
}

#include <iostream>
namespace ford_johson
{
template <typename Iterator>
void print_iter_array(Iterator *arr, std::size_t size)
{
	for (std::size_t i = 0; i < size; ++i)
	{
		std::cout << *arr[i];
		std::cout.flush();
		if (i + 1 < size)
			std::cout << ' ';
	}
	std::cout << '\n';
}

template <typename Iterator> struct s_Block
{
	Iterator *block_start; // Iterador real al elemento
	s_Block *pair;         // Puntero a su pareja (a_i <-> b_i)
	bool is_big;           // true = bloque grande (b_i), false = pequeño (a_i)
	std::size_t block_index; // Índice del bloque al que pertenece
	unsigned int block_value;
	bool inserted;
};

/**
 * @struct s_JacobsthalSeq
 * An struct containing an array with several Jacobsthal Numbers
 *
 * @param seq A fixed array for containing the numbers. It's size is 64 because
 *            65th Jacobsthal number is bigger than SIZE_MAX in 64 bits.
 * @param size Size of the sequence.
 */
struct s_JacobsthalSeq
{
	std::size_t seq[64];
	std::size_t size;
};

template <typename Iterator> struct s_SequenceContainer
{
	s_Block<Iterator> *main;
	std::size_t main_size;
	s_Block<Iterator> *pend;
	std::size_t pend_size;
};

template <typename Iterator> struct FJState
{
	Iterator *it_array;     // array de iteradores (entrada)
	std::size_t size;       // número total de elementos
	std::size_t block_size; // tamaño del bloque actual

	s_SequenceContainer<Iterator> container; // MAIN + PEND

	Iterator *buffer;            // buffer donde se insertan los bloques
	std::size_t inserted_blocks; // bloques ya insertados (big + small)

	s_JacobsthalSeq js;     // secuencia Jacobsthal para PEND
	std::size_t last_start; // último índice Jacobsthal procesado
};

template <typename Iterator>
void debug_print_main_and_pend_one_line(const FJState<Iterator> &st)
{
	typedef typename std::iterator_traits<Iterator>::value_type value_t;

	std::cerr << "DBG STATE size=" << st.size << " block_size=" << st.block_size
	          << " main_size=" << st.container.main_size
	          << " pend_size=" << st.container.pend_size << "\n";

	std::cerr << "DBG SEQ:";
	// Primero MAIN (bloques en orden)
	for (std::size_t b = 0; b < st.container.main_size; ++b)
	{
		Iterator *block_start = st.container.main[b].block_start;
		std::ptrdiff_t idx = block_start - st.it_array;
		if (idx < 0 || static_cast<std::size_t>(idx) + st.block_size > st.size)
		{
			std::cerr << " [MAIN[" << b << "] OUT_OF_RANGE]";
			continue;
		}
		std::cerr << " [M" << b << ":";
		for (std::size_t k = 0; k < st.block_size; ++k)
		{
			value_t v = *block_start[k];
			std::cerr << (k ? " " : "") << v;
		}
		std::cerr << "]";
	}

	// Luego PEND (bloques en orden)
	for (std::size_t p = 0; p < st.container.pend_size; ++p)
	{
		Iterator *block_start = st.container.pend[p].block_start;
		std::ptrdiff_t idx = block_start - st.it_array;
		if (idx < 0 || static_cast<std::size_t>(idx) + st.block_size > st.size)
		{
			std::cerr << " [PEND[" << p << "] OUT_OF_RANGE]";
			continue;
		}
		std::cerr << " [P" << p << ":";
		for (std::size_t k = 0; k < st.block_size; ++k)
		{
			value_t v = *block_start[k];
			std::cerr << (k ? " " : "") << v;
		}
		std::cerr << "]";
	}

	std::cerr << "\n";
}

#include <iostream>

template <typename Iterator>
void link_pairs(s_SequenceContainer<Iterator> &container)
{
	// Nada que hacer si no hay mains
	if (container.main_size == 0)
		return;

	// Si no hay al menos 2 mains, no podemos enlazar MAIN[0] con MAIN[1]
	if (container.main_size >= 2)
	{
		// MAIN[0] es small, su pareja es MAIN[1]
		container.main[0].pair = &container.main[1];
		container.main[0].is_big = false;
		container.main[1].is_big = true;
	}
	else
	{
		std::cerr << "link_pairs_simple: main_size < 2, no se puede enlazar "
		             "MAIN[0] con MAIN[1]\n";
	}

	// Emparejar cada pend[p] con MAIN[2 + p]
	for (std::size_t p = 0; p < container.pend_size; ++p)
	{
		std::size_t main_idx = 2 + p;
		if (main_idx < container.main_size)
		{
			container.pend[p].pair = &container.main[main_idx];
			// mantener block_index coherente (opcional)
			// container.pend[p].block_index = p;
		}
		else
		{
			container.pend[p].pair = NULL;
			std::cerr << "link_pairs_simple: no existe MAIN[" << main_idx
			          << "] para emparejar PEND[" << p << "]\n";
		}
	}
}

/* template <typename Iterator>
s_SequenceContainer<Iterator>
build_sequences(Iterator *it_array, std::size_t size, std::size_t block_size)
{
    s_SequenceContainer<Iterator> container;

    // Número de bloques COMPLETOS
    std::size_t total_blocks = size / block_size;

    // Si no hay bloques completos → no hay secuencias
    if (total_blocks == 0)
    {
        container.main = NULL;
        container.main_size = 0;
        container.pend = NULL;
        container.pend_size = 0;
        return container;
    }

    // MAIN = bloque 0 + impares
    std::size_t main_blocks = 1 + total_blocks / 2;

    // PEND = pares > 0
    std::size_t pend_blocks = (total_blocks > 1 ? (total_blocks - 1) / 2 : 0);

    container.main = new s_Block<Iterator>[main_blocks];
    container.main_size = main_blocks;

    container.pend = new s_Block<Iterator>[pend_blocks];
    container.pend_size = pend_blocks;

    std::size_t main_i = 0;
    std::size_t pend_i = 0;

    for (std::size_t block = 0; block < total_blocks; ++block)
    {
        Iterator *block_start = &it_array[block * block_size];

        s_Block<Iterator> info;
        info.block_start = block_start;
        info.pair = NULL;
        info.is_big = false;
        info.block_value = 0;

        if (block == 0 || (block % 2 == 1))
        {
            info.block_index = main_i;
            container.main[main_i++] = info;
        }
        else
        {
            info.block_index = pend_i;
            container.pend[pend_i++] = info;
        }
    }

    // link_pairs(container);

    return container;
} */

template <typename Iterator>
s_SequenceContainer<Iterator>
build_sequences(Iterator *it_array, std::size_t size, std::size_t block_size)
{
	s_SequenceContainer<Iterator> container;

	if (block_size == 0)
	{
		// defensivo: no permitir block_size 0
		container.main = NULL;
		container.main_size = 0;
		container.pend = NULL;
		container.pend_size = 0;
		return container;
	}

	// Número de bloques COMPLETOS
	std::size_t total_blocks = size / block_size;

	// Si no hay bloques completos → no hay secuencias
	if (total_blocks == 0)
	{
		container.main = NULL;
		container.main_size = 0;
		container.pend = NULL;
		container.pend_size = 0;
		return container;
	}

	// MAIN = bloque 0 + impares
	std::size_t main_blocks = 1 + total_blocks / 2;

	// PEND = pares > 0
	std::size_t pend_blocks = (total_blocks > 1 ? (total_blocks - 1) / 2 : 0);

	container.main = new s_Block<Iterator>[main_blocks];
	container.main_size = main_blocks;

	container.pend = new s_Block<Iterator>[pend_blocks];
	container.pend_size = pend_blocks;

	std::size_t main_i = 0;
	std::size_t pend_i = 0;

	for (std::size_t block = 0; block < total_blocks; ++block)
	{
		Iterator *block_start = &it_array[block * block_size];

		s_Block<Iterator> info;
		info.block_start = block_start;
		info.pair = NULL;
		info.is_big = false;
		info.inserted = false;

		// Asignar block_value: último elemento del bloque (defensivo)
		std::size_t last_offset = block_size - 1;
		std::size_t last_index = block * block_size + last_offset;
		if (last_index < size)
		{
			info.block_value =
			    static_cast<unsigned int>(*block_start[last_offset]);
		}
		else
		{
			// No debería ocurrir si total_blocks calculado correctamente,
			// pero por seguridad asignamos el primer elemento del bloque.
			info.block_value = static_cast<unsigned int>(*block_start[0]);
		}

		if (block == 0 || (block % 2 == 1))
		{
			info.block_index = main_i;
			container.main[main_i++] = info;
		}
		else
		{
			info.block_index = pend_i;
			container.pend[pend_i++] = info;
		}
	}

	link_pairs(container); // si lo necesitas, descomenta

	return container;
}

/* template <typename Iterator>
Iterator *build_insertion_buffer(Iterator *it_array,
                                 const s_SequenceContainer<Iterator> &container,
                                 std::size_t size, std::size_t block_size)
{
    // 1. Crear buffer del mismo tamaño que it_array
    Iterator *buffer = new Iterator[size];

    std::size_t pos = 0;

    // 2. Copiar todos los bloques de MAIN al principio del buffer
    for (std::size_t b = 0; b < container.main_size; ++b)
    {
        Iterator *block_start = container.main[b].block_start;

        for (std::size_t k = 0; k < block_size; ++k)
        {
            buffer[pos++] = block_start[k];
        }
    }

    // 3. Calcular cuántos elementos son sobrantes
    std::size_t used_by_main = container.main_size * block_size;
    std::size_t used_by_pend = container.pend_size * block_size;

    std::size_t leftover = 0;
    if (size > used_by_main + used_by_pend)
        leftover = size - (used_by_main + used_by_pend);

    // 4. Copiar los SOBRANTES al final del buffer
    //    Los sobrantes están al final de it_array
    for (std::size_t i = size - leftover; i < size; ++i)
    {
        buffer[pos++] = it_array[i];
    }

    return buffer;
} */

template <typename Iterator>
Iterator *build_insertion_buffer(Iterator *it_array,
                                 const s_SequenceContainer<Iterator> &container,
                                 std::size_t size, std::size_t block_size)
{
	Iterator *buffer = new Iterator[size];
	std::size_t pos = 0;

	// 1) Copiar MAIN
	for (std::size_t b = 0; b < container.main_size; ++b)
	{
		Iterator *block_start = container.main[b].block_start;
		std::ptrdiff_t idx = block_start - it_array;
		if (idx < 0 || static_cast<std::size_t>(idx) + block_size > size)
		{
			std::cerr << "FATAL: main block_start out of bounds b=" << b
			          << " idx=" << idx << "\n";
			abort();
		}
		for (std::size_t k = 0; k < block_size; ++k)
		{
			if (pos >= size)
			{
				std::cerr << "FATAL: buffer overflow copying MAIN pos=" << pos
				          << "\n";
				abort();
			}
			buffer[pos++] = block_start[k];
		}
	}

	// 2) Reservar hueco para PEND (no escribir, solo avanzar pos)
	std::size_t hole = container.pend_size * block_size;
	if (pos + hole > size)
	{
		std::cerr << "FATAL: not enough space to reserve hole pos=" << pos
		          << " hole=" << hole << " size=" << size << "\n";
		abort();
	}
	// Opcional: si quieres marcar el hueco con un valor reconocible, puedes
	// hacerlo aquí.
	pos += hole;

	// 3) Copiar leftover (si existe)
	std::size_t used_by_main = container.main_size * block_size;
	std::size_t used_by_pend = container.pend_size * block_size;
	std::size_t leftover = 0;
	if (size > used_by_main + used_by_pend)
		leftover = size - (used_by_main + used_by_pend);

	if (leftover > 0)
	{
		std::size_t start = size - leftover;
		if (start > size)
		{
			std::cerr << "FATAL: start > size\n";
			abort();
		}
		for (std::size_t i = start; i < size; ++i)
		{
			if (pos >= size)
			{
				std::cerr << "FATAL: buffer overflow copying leftover pos="
				          << pos << "\n";
				abort();
			}
			buffer[pos++] = it_array[i];
		}
	}

	// Comprobación final
	if (pos != size)
	{
		std::cerr << "WARN: build_insertion_buffer finished pos=" << pos
		          << " expected=" << size << "\n";
	}

	// DEBUG: comprobar que el buffer tiene exactamente 'size' elementos
	// inicializados
	std::cerr << "DBG build_insertion_buffer: final pos=" << pos
	          << " expected size=" << size << "\n";

	return buffer;
}

template <typename Iterator>
std::size_t binary_search_block_pos(unsigned int value, Iterator *buffer,
                                    std::size_t start_block,
                                    std::size_t end_block,
                                    std::size_t block_size)
{
	if (block_size == 0)
		return 0;

	// Caso trivial: rango vacío
	if (start_block > end_block)
		return start_block;

	// right es exclusivo
	std::size_t left = start_block;
	std::size_t right = end_block + 1;

	while (left < right)
	{
		std::size_t mid = left + (right - left) / 2;

		// Índice del último elemento del bloque mid
		std::size_t last_index = (mid + 1) * block_size - 1;

		// Comparación por valor
		unsigned int mid_value = *buffer[last_index];

		if (value <= mid_value)
			right = mid;
		else
			left = mid + 1;
	}

	return left;
}

/* template <typename Iterator>
void shift_right(Iterator *arr, std::size_t from_index, std::size_t count,
                 std::size_t shift)
{
    if (count == 0 || shift == 0)
        return;
    for (std::size_t i = count; i > 0; --i)
        arr[from_index + i - 1 + shift] = arr[from_index + i - 1];
} */
template <typename Iterator>
void shift_right(Iterator *arr, std::size_t from_index, std::size_t count,
                 std::size_t shift, std::size_t total_size)
{
	if (count == 0 || shift == 0)
		return;

	// Comprobación de límites: último índice destino = from_index + count - 1 +
	// shift
	if (from_index + count - 1 + shift >= total_size)
	{
		std::cerr << "FATAL: shift_right out of bounds from_index="
		          << from_index << " count=" << count << " shift=" << shift
		          << " last_dest_index=" << (from_index + count - 1 + shift)
		          << " total_size=" << total_size << "\n";
		abort();
	}

	// Copiar de derecha a izquierda para evitar sobrescribir origen
	for (std::size_t i = count; i > 0; --i)
		arr[from_index + i - 1 + shift] = arr[from_index + i - 1];
}

template <typename Iterator>
void insert_block_into_main(FJState<Iterator> &st, std::size_t pend_block_index)
{

	// 0. Validaciones iniciales
	if (pend_block_index >= st.container.pend_size)
	{
		std::cerr
		    << "WARN: insert_block_into_main: pend_block_index out of range: "
		    << pend_block_index << "\n";
		return;
	}

	s_Block<Iterator> &small = st.container.pend[pend_block_index];

	// Si ya fue insertado, saltar
	if (small.inserted)
	{
		std::cerr << "WARN: insert_block_into_main: pend_idx="
		          << pend_block_index << " ya insertado, saltando\n";
		return;
	}

	// total_blocks (número de bloques completos)
	std::size_t total_blocks = st.size / st.block_size;
	if (st.inserted_blocks >= total_blocks)
	{
		std::cerr << "WARN: insert_block_into_main: no hay bloques libres para "
		             "insertar pend_idx="
		          << pend_block_index
		          << " (inserted_blocks=" << st.inserted_blocks
		          << " total_blocks=" << total_blocks << ")\n";
		return;
	}
	s_SequenceContainer<Iterator> &container = st.container;
	Iterator *buffer = st.buffer;
	std::size_t block_size = st.block_size;

	// 1. Bloque pequeño a insertar
	Iterator *block_start = small.block_start;
	unsigned int key = small.block_value;

	// 2. Calcular upper bound usando la pareja (bloque grande)
	std::size_t upper = st.inserted_blocks; // fallback

	if (small.pair != NULL)
	{
		std::size_t big_pos = small.pair->block_index;

		// upper = posición del big + 1
		upper = big_pos + 1;

		if (upper > st.inserted_blocks)
			upper = st.inserted_blocks;
	}

	// 3. Binary search REAL dentro del rango permitido
	std::size_t target_pos =
	    (upper == 0) ? 0
	                 : binary_search_block_pos(key, buffer, 0,
	                                           upper - 1, // ¡IMPORTANTE!
	                                           block_size);

	/*
	// 4. shift_right para abrir hueco
	std::size_t from_index = target_pos * block_size;
	std::size_t count = st.inserted_blocks * block_size - from_index;

	// shift_right(buffer, from_index, count, block_size);
	shift_right(buffer, from_index, count, block_size, st.size);
	*/

	// 4. shift_right para abrir hueco
	std::size_t from_index = target_pos * block_size;
	std::size_t count = 0;
	if (st.inserted_blocks * block_size > from_index)
		count = st.inserted_blocks * block_size - from_index;
	else
		count = 0;

	// TRACE antes de shift
	std::cerr << "DBG insert_block_into_main: pend_idx=" << pend_block_index
	          << " target_pos=" << target_pos << " from_index=" << from_index
	          << " count=" << count << " shift(block_size)=" << block_size
	          << " inserted_blocks=" << st.inserted_blocks
	          << " st.size=" << st.size << "\n";

	// Llamada segura (Opción A)
	shift_right(buffer, from_index, count, block_size, st.size);

	// 5. Copiar el bloque dentro del hueco
	std::size_t base = target_pos * block_size;
	for (std::size_t k = 0; k < block_size; ++k)
		buffer[base + k] = block_start[k];

	// TRACE: mostrar primer y último elemento del hueco insertado
	if (block_size > 0)
	{
		std::cerr << "DBG insert_block_into_main: inserted block at base="
		          << base << " first=" << *buffer[base]
		          << " last=" << *buffer[base + block_size - 1] << "\n";
	}

	// 6. Actualizar block_index de los bloques del MAIN
	//    Todos los bloques grandes con block_index >= target_pos
	//    deben desplazarse una posición hacia abajo.
	std::size_t i;
	for (i = 0; i < container.main_size; ++i)
	{
		if (container.main[i].block_index >= target_pos)
			container.main[i].block_index++;
	}

	// 7. El bloque pequeño insertado ahora forma parte del MAIN
	small.block_index = target_pos;

	// 8. Incrementar contador global de bloques insertados
	st.inserted_blocks++;

	small.inserted = true;

	std::cout << "Inserted!" << std::endl;
}

/**
 * @brief Builds and returns a s_JacobsthalSeq.
 *
 * It generates a sequence of Jacobsthal's numbers, a sequence where a number
 * is the sum of the previous and two times the preovious before that. The
 * sequence is returned in a 0 based basis.
 *
 * @param size Number of Jacobsthal numbers required.
 *
 * @return A s_JacobsthalSeq object containing the required sequence.
 */
s_JacobsthalSeq buildJacobsthalSeq(std::size_t size);

template <typename Iterator>
void process_jacobsthal_blocks(FJState<Iterator> &fj_state)
{
	s_SequenceContainer<Iterator> &container = fj_state.container;
	const s_JacobsthalSeq &js = fj_state.js;

	// Si no hay bloques pequeños, no hay nada que procesar
	if (container.pend_size == 0)
		return;

	for (std::size_t i = 0; i < js.size; ++i)
	{
		// js.seq[] ya es 0-based → NO restar 1
		std::size_t start = js.seq[i];
		std::size_t end = (i > 0 ? js.seq[i - 1] : 0);

		// Clamp por seguridad
		if (start >= container.pend_size)
		{
			fj_state.last_start = container.pend_size - 1;
			return; // ← detener Jacobsthal
		}
		if (end >= container.pend_size)
			end = container.pend_size - 1;

		// Insertar en orden descendente
		std::size_t j = start + 1;
		while (j-- > end)
		{
			insert_block_into_main(fj_state, j);
		}

		// Después de procesar el bloque Jacobsthal (ya se han llamado
		// insert_block_into_main)
		std::size_t inserted_pend = 0;
		if (fj_state.inserted_blocks > container.main_size)
			inserted_pend = fj_state.inserted_blocks - container.main_size;
		fj_state.last_start = inserted_pend;
	}
}
/*
template <typename Iterator>
void process_remaining_blocks(FJState<Iterator> &fj_state)
{
    s_SequenceContainer<Iterator> &container = fj_state.container;

    // Si no hay bloques pequeños, no hay nada que hacer
    if (container.pend_size == 0)
        return;

    // Bloques pequeños ya insertados
    std::size_t inserted_pend = 0;
    if (fj_state.inserted_blocks > container.main_size)
        inserted_pend = fj_state.inserted_blocks - container.main_size;

    // Si ya están todos insertados → salir
    if (inserted_pend >= container.pend_size)
        return;

    // Bloques pequeños que faltan por insertar
    std::size_t remaining = container.pend_size - inserted_pend;

    // Insertar en orden descendente
    std::size_t j = fj_state.last_start + remaining;
    while (j-- > fj_state.last_start)
    {
        insert_block_into_main(fj_state, j);
    }
} */
template <typename Iterator>
void process_remaining_blocks(FJState<Iterator> &fj_state)
{
	s_SequenceContainer<Iterator> &container = fj_state.container;

	if (container.pend_size == 0)
		return;

	// Cuántos PEND ya insertados
	std::size_t inserted_pend = 0;
	if (fj_state.inserted_blocks > container.main_size)
		inserted_pend = fj_state.inserted_blocks - container.main_size;

	if (inserted_pend >= container.pend_size)
		return;

	// Insertar todos los PEND restantes, en orden ascendente
	for (std::size_t idx = inserted_pend; idx < container.pend_size; ++idx)
	{
		insert_block_into_main(fj_state, idx);
	}

	// Actualizar last_start al primer índice no procesado (aquí, ninguno)
	fj_state.last_start = container.pend_size;
}

template <typename Iterator>
FJState<Iterator> init_fj_state(Iterator *it_array, std::size_t size,
                                std::size_t block_size)
{
	FJState<Iterator> st;

	st.it_array = it_array;
	st.size = size;
	st.block_size = block_size;
	// 1. Construir secuencias MAIN y PEND
	st.container = build_sequences(it_array, size, block_size);

	// Si no hay bloques completos → no hay nada que hacer
	if (st.container.main_size == 0)
	{
		st.buffer = NULL;
		st.inserted_blocks = 0;
		st.last_start = 0;
		st.js.size = 0;
		return st;
	}

	// 2. Construir buffer inicial (MAIN + sobrantes)
	st.buffer =
	    build_insertion_buffer(it_array, st.container, size, block_size);

	// 3. Inicializar contadores
	st.inserted_blocks = st.container.main_size; // los big ya están en buffer
	st.last_start = 0;

	// 4. Construir secuencia Jacobsthal para los bloques pequeños
	st.js = buildJacobsthalSeq(st.container.pend_size);

	debug_print_main_and_pend_one_line(st);

	return st;
}

template <typename Iterator>
Iterator *ford_johson_insertion(Iterator *it_array, std::size_t block_size,
                                std::size_t size)
{
	// std::cout << "it_array =  " << block_size;
	print_iter_array(it_array, size);
	// Caso base
	if (block_size == 0 || block_size >= size)
		return it_array;
	FJState<Iterator> fj_state = init_fj_state(it_array, size, block_size);

	// Si no hay bloques grandes, no se puede continuar
	if (fj_state.container.main_size == 0)
		return it_array;

	process_jacobsthal_blocks(fj_state);

	// ---------------------------------------------------------
	// 5. Insertar los bloques pequeños restantes
	// ---------------------------------------------------------
	process_remaining_blocks(fj_state);

	// ---------------------------------------------------------
	// 7. Recursión con block_size / 2
	// ---------------------------------------------------------

	Iterator *result =
	    ford_johson_insertion(fj_state.buffer, block_size / 2, size);

	// ---------------------------------------------------------
	// 8. Liberar memoria de estructuras auxiliares
	// ---------------------------------------------------------
	delete[] fj_state.container.main;
	delete[] fj_state.container.pend;
	delete[] it_array;

	return result;
}

/**
 * @brief Builds the iterator array from the original container
 *
 * @param Container Reference to the original container.
 * @param size Number of elements inside the container.
 */
template <typename Container>
typename Container::iterator *get_iterator_array(Container &cont,
                                                 std::size_t size)
{
	typedef typename Container::iterator iterator;

	iterator *it_array = new iterator[size];
	iterator it = cont.begin();

	for (std::size_t i = 0; i < size; ++i)
		it_array[i] = it++;
	return it_array;
}

/**
 * @brief Swaps two blocks inside an array
 *
 * It swap the positions of a given block with the one next to it
 *
 * @param it_array Array containing all iterators
 * @param block_size Size of the given block
 * @param pos Position inside the array of the given block
 */
template <typename Iterator>
void swap_blocks(Iterator *it_array, std::size_t block_size, std::size_t pos)
{
	for (std::size_t i = pos; i < pos + block_size; ++i)
		std::swap(it_array[i], it_array[i + block_size]);
}

/**
 * @brief Orders adjacent block pairs for the Ford–Johnson algorithm.
 *
 * Compares each pair of consecutive blocks of size `block_size` using their
 * last elements as keys. If the first block is greater, the two blocks are
 * swapped. After processing all pairs, the function recurses with doubled
 * block size.
 *
 * @param it_array   Array of iterators.
 * @param block_size Current block size.
 * @param size       Total number of elements.
 *
 * @return The same pointer `it_array` after pair ordering.
 */
template <typename Iterator>
Iterator *ford_johnson_pairs(Iterator *it_array, std::size_t block_size,
                             size_t size)
{
	if (block_size == 0 || block_size >= size)
		return it_array;

	std::size_t double_block_size = block_size * 2;

	for (size_t i = 0; i + double_block_size <= size; i += double_block_size)
	{
		if (*it_array[i + block_size - 1] >
		    *it_array[i + double_block_size - 1])
			swap_blocks(it_array, block_size, i);
	}

	return ford_johnson_pairs(it_array, double_block_size, size);
}

/**
 * @brief Runs the full Ford–Johnson sorting procedure on a container.
 *
 * Converts the container into an iterator array, performs the pairing phase
 * starting with block size 1, determines the largest power-of-two block size
 * for insertion, and executes the Ford–Johnson insertion phase. Returns the
 * final sorted iterator array.
 *
 * @param cont Input container.
 * @return Pointer to the sorted iterator array.
 */
template <typename Container>
typename Container::iterator *ford_johnson(Container &cont)
{
	typedef typename Container::iterator iterator;
	std::size_t size = cont.size();

	iterator *it_array =
	    ford_johnson_pairs(get_iterator_array(cont, size), 1, size);
	std::size_t block = 1;
	while (block * 2 <= size)
		block *= 2;

	block /= 2; // First level

	it_array = ford_johson_insertion(it_array, block, size);

	return it_array;
}
} // namespace ford_johson

#endif
