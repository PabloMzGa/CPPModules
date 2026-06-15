template <typename Iterator>
s_FJBlockInfo< s_Block<Iterator> >
build_fj_block_info(Iterator *it_array,
                    std::size_t block_size,
                    std::size_t size)
{
    typedef s_Block<Iterator> Block;
    s_FJBlockInfo<Block> info;

    info.main = NULL;
    info.pend = NULL;
    info.main_size = 0;
    info.main_blocks = 0;
    info.pend_blocks = 0;
    info.pend_size = 0;
    info.block_size = block_size;
    info.total_size = size;
    info.inserted_blocks = 0;

    if (block_size == 0 || block_size >= size)
        return info;

    // Reservar arrays destino (máximo 'size' elementos por simplicidad)
    info.main = new Block[size];
    info.pend = new Block[size];

    // 1) Construir array plano de bloques temporales (uno por elemento del it_array,
    //    pero cada bloque tendrá su propio array dinámico de iteradores cuando corresponda)
    Block *flat = new Block[size];
    for (std::size_t i = 0; i < size; ++i)
    {
        flat[i].block = NULL;
        flat[i].pair = NULL;
        flat[i].is_big = false;
        flat[i].block_index = i; // temporal, se ajustará por bloque lógico
        flat[i].block_value = 0;
    }

    // 2) Para cada bloque lógico, crear su array de iteradores y rellenarlo
    std::size_t blocks_count = (size + block_size - 1) / block_size;
    for (std::size_t b = 0; b < blocks_count; ++b)
    {
        std::size_t start = b * block_size;
        std::size_t current = std::min(block_size, size - start);

        // Crear array dinámico para este bloque y copiar iteradores
        Iterator *blk_arr = new Iterator[current];
        for (std::size_t j = 0; j < current; ++j)
            blk_arr[j] = it_array[start + j];

        // Guardar la información del bloque en las posiciones correspondientes de flat
        for (std::size_t j = 0; j < current; ++j)
        {
            std::size_t idx = start + j;
            flat[idx].block = blk_arr;                 // mismo puntero para todos los elementos del bloque
            flat[idx].block_index = b;                 // índice del bloque lógico
            // block_value = valor del último elemento del bloque (para comparaciones)
            flat[idx].block_value = static_cast<unsigned int>(*blk_arr[current - 1]);
        }
    }

    // 3) Asignar parejas entre bloques lógicos pares (a) y su siguiente (b)
    for (std::size_t b = 0; b + 1 < blocks_count; b += 2)
    {
        // Última posición del bloque a y del bloque b (índices en flat)
        std::size_t a_last = b * block_size + (block_size - 1);
        std::size_t b_last = (b + 1) * block_size + (block_size - 1);

        // Si alguno de los índices excede size, ajustamos al último válido del bloque
        if (a_last >= size) a_last = std::min(size - 1, b * block_size + (std::size_t)(block_size - 1));
        if (b_last >= size) b_last = std::min(size - 1, (b + 1) * block_size + (std::size_t)(block_size - 1));

        // Apuntar parejas a los bloques (usamos la última posición representativa)
        Block *a_rep = &flat[a_last];
        Block *b_rep = &flat[b_last];

        // Apuntar pair en todas las entradas del bloque a y b (opcional, pero útil)
        // Aquí enlazamos las representativas; al copiar a main/pend se conservará el puntero.
        a_rep->pair = b_rep;
        b_rep->pair = a_rep;

        // Marcar is_big comparando block_value (último elemento)
        if (a_rep->block_value > b_rep->block_value)
        {
            a_rep->is_big = true;
            b_rep->is_big = false;
        }
        else
        {
            a_rep->is_big = false;
            b_rep->is_big = true;
        }
    }

    // 4) Distribuir en main / pend respetando la regla original (por elemento)
    std::size_t main_i = 0;
    std::size_t pend_i = 0;

    for (std::size_t i = 0; i < size; i += block_size)
    {
        std::size_t block = i / block_size;
        std::size_t current = std::min(block_size, size - i);

        bool goes_to_main = (block == 0 || block % 2 == 1);
        bool full_block = (current == block_size);

        if (!full_block && block != 0)
            goes_to_main = false;

        for (std::size_t j = 0; j < current; ++j)
        {
            Block &src = flat[i + j];

            if (goes_to_main)
            {
                info.main[(main_i * block_size) + j] = src;
                ++info.main_size;
            }
            else
            {
                info.pend[pend_i] = src;
                ++info.pend_size;
                ++pend_i;
            }
        }

        if (goes_to_main)
            ++main_i;
        else if (full_block)
            ++info.pend_blocks;
    }

    info.main_blocks = main_i;

    // NOTA: no borramos los arrays internos blk_arr aquí porque info.main/info.pend
    // contienen punteros a esos arrays. El llamador debe liberar la memoria interna
    // cuando ya no necesite info.main/info.pend (ver helper abajo).

    delete[] flat;
    return info;
}
